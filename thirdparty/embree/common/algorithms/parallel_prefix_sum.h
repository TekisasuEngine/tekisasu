/**************************************************************************/
/*  parallel_prefix_sum.h                                                 */
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
  template<typename Value>
    struct ParallelPrefixSumState 
  {
    enum { MAX_TASKS = 64 };
    Value counts[MAX_TASKS];
    Value sums  [MAX_TASKS];
  };

  template<typename Index, typename Value, typename Func, typename Reduction>
    __forceinline Value parallel_prefix_sum( ParallelPrefixSumState<Value>& state, Index first, Index last, Index minStepSize, const Value& identity, const Func& func, const Reduction& reduction)
  {
    /* calculate number of tasks to use */
    const size_t numThreads = TaskScheduler::threadCount();
    const size_t numBlocks  = (last-first+minStepSize-1)/minStepSize;
    const size_t taskCount  = min(numThreads,numBlocks,size_t(ParallelPrefixSumState<Value>::MAX_TASKS));

    /* perform parallel prefix sum */
    parallel_for(taskCount, [&](const size_t taskIndex)
    {
      const size_t i0 = first+(taskIndex+0)*(last-first)/taskCount;
      const size_t i1 = first+(taskIndex+1)*(last-first)/taskCount;
      state.counts[taskIndex] = func(range<size_t>(i0,i1),state.sums[taskIndex]);
    });

    /* calculate prefix sum */
    Value sum=identity;
    for (size_t i=0; i<taskCount; i++) 
    {
      const Value c = state.counts[i];
      state.sums[i] = sum;
      sum=reduction(sum,c);
    }

    return sum;
  }

  /*! parallel calculation of prefix sums */
  template<typename SrcArray, typename DstArray, typename Value, typename Add>
    __forceinline Value parallel_prefix_sum(const SrcArray& src, DstArray& dst, size_t N, const Value& identity, const Add& add, const size_t SINGLE_THREAD_THRESHOLD = 4096) 
  {
    /* perform single threaded prefix operation for small N */
    if (N < SINGLE_THREAD_THRESHOLD) 
    {
      Value sum=identity;
      for (size_t i=0; i<N; sum=add(sum,src[i++])) dst[i] = sum;
      return sum;
    }
    
    /* perform parallel prefix operation for large N */
    else 
    {
      ParallelPrefixSumState<Value> state;
      
      /* initial run just sets up start values for subtasks */
      parallel_prefix_sum( state, size_t(0), size_t(N), size_t(1024), identity, [&](const range<size_t>& r, const Value& sum) -> Value {
          
          Value s = identity;
          for (size_t i=r.begin(); i<r.end(); i++) s = add(s,src[i]);
          return s;
          
        }, add);
      
      /* final run calculates prefix sum */
      return parallel_prefix_sum( state, size_t(0), size_t(N), size_t(1024), identity, [&](const range<size_t>& r, const Value& sum) -> Value {
          
          Value s = identity;
          for (size_t i=r.begin(); i<r.end(); i++) {
            dst[i] = add(sum,s);
            s = add(s,src[i]);
          }
          return s;
          
        }, add);
    }
  }
}
