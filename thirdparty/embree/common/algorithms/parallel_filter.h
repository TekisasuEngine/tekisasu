/**************************************************************************/
/*  parallel_filter.h                                                     */
/**************************************************************************/
/*                         This file is part of:                          */
/*                            TEKISASU ENGINE                             */
/*                       https://dev.tekisasu.com                         */
/**************************************************************************/
/* Copyright (c) 2021-present Tekisasu (see AUTHORS.md).                  */
/* Copyright (c) 2024-present Blazium (see BLAZIUM.md).                   */
/* Copyright (c) 2024-present Redot Engine contributors (see REDOT.md).   */
/* Copyright (c) 2014-present Godot Engine contributors (see GODOT.md).   */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

// Copyright 2009-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "parallel_for.h"

namespace embree
{
  template<typename Ty, typename Index, typename Predicate>
    inline Index sequential_filter( Ty* data, const Index first, const Index last, const Predicate& predicate)
  {
    Index j = first;
    for (Index i=first; i<last; i++)
      if (predicate(data[i]))
        data[j++] = data[i];

    return j;
  }

  template<typename Ty, typename Index, typename Predicate>
    inline Index parallel_filter( Ty* data, const Index begin, const Index end, const Index minStepSize, const Predicate& predicate)
  {
    /* sequential fallback */
    if (end-begin <= minStepSize)
      return sequential_filter(data,begin,end,predicate);

    /* calculate number of tasks to use */
    enum { MAX_TASKS = 64 };
    const Index numThreads = TaskScheduler::threadCount();
    const Index numBlocks  = (end-begin+minStepSize-1)/minStepSize;
    const Index taskCount  = min(numThreads,numBlocks,(Index)MAX_TASKS);

    /* filter blocks */
    Index nused[MAX_TASKS];
    Index nfree[MAX_TASKS];
    parallel_for(taskCount, [&](const Index taskIndex)
    {
      const Index i0 = begin+(taskIndex+0)*(end-begin)/taskCount;
      const Index i1 = begin+(taskIndex+1)*(end-begin)/taskCount;
      const Index i2 = sequential_filter(data,i0,i1,predicate);
      nused[taskIndex] = i2-i0;
      nfree[taskIndex] = i1-i2;
    });

    /* calculate offsets */
    Index sused=0;
    Index sfree=0;
    Index pfree[MAX_TASKS];
    for (Index i=0; i<taskCount; i++) 
    {
      sused+=nused[i];
      Index cfree = nfree[i]; pfree[i] = sfree; sfree+=cfree;
    }

    /* return if we did not filter out any element */
    assert(sfree <= end-begin);
    assert(sused <= end-begin);
    if (sused == end-begin)
      return end;

    /* otherwise we have to copy misplaced elements around */
    parallel_for(taskCount, [&](const Index taskIndex)
    {
      /* destination to write elements to */
      Index dst = begin+(taskIndex+0)*(end-begin)/taskCount+nused[taskIndex];
      Index dst_end = min(dst+nfree[taskIndex],begin+sused);
      if (dst_end <= dst) return;

      /* range of misplaced elements to copy to destination */
      Index r0 = pfree[taskIndex];
      Index r1 = r0+dst_end-dst;

      /* find range in misplaced elements in back to front order */
      Index k0=0;
      for (Index i=taskCount-1; i>0; i--)
      {
        if (k0 > r1) break;
        Index k1 = k0+nused[i];
        Index src = begin+(i+0)*(end-begin)/taskCount+nused[i];
        for (Index i=max(r0,k0); i<min(r1,k1); i++) {
          Index isrc = src-i+k0-1;
          assert(dst >= begin && dst < end);
          assert(isrc >= begin && isrc < end);
          data[dst++] = data[isrc];
        }
        k0 = k1;
      }
    });

    return begin+sused;
  }
}
