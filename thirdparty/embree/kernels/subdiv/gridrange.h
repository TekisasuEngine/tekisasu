/**************************************************************************/
/*  gridrange.h                                                           */
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

#include "../common/default.h"

namespace embree
{
  struct __aligned(16) GridRange
  {
    unsigned int u_start;
    unsigned int u_end;
    unsigned int v_start;
    unsigned int v_end;

    __forceinline GridRange() {}

    __forceinline GridRange(unsigned int u_start, unsigned int u_end, unsigned int v_start, unsigned int v_end) 
      : u_start(u_start), u_end(u_end), v_start(v_start), v_end(v_end) {}

    __forceinline unsigned int width() const {
      return u_end-u_start+1;
    }

    __forceinline unsigned int height() const {
      return v_end-v_start+1;
    }

    __forceinline bool hasLeafSize() const
    {
      const unsigned int u_size = u_end-u_start+1;
      const unsigned int v_size = v_end-v_start+1;
      assert(u_size >= 1);
      assert(v_size >= 1);
      return u_size <= 3 && v_size <= 3;
    }

    static __forceinline unsigned int split(unsigned int start,unsigned int end)
    {
      const unsigned int center = (start+end)/2;
      assert (center > start);
      assert (center < end);
      return center;
    }

    __forceinline void split(GridRange& r0, GridRange& r1) const
    {
      assert( hasLeafSize() == false );
      const unsigned int u_size = u_end-u_start+1;
      const unsigned int v_size = v_end-v_start+1;
      r0 = *this;
      r1 = *this;

      if (u_size >= v_size)
      {
        const unsigned int u_mid = split(u_start,u_end);
        r0.u_end   = u_mid;
        r1.u_start = u_mid;
      }
      else
      {
        const unsigned int v_mid = split(v_start,v_end);
        r0.v_end   = v_mid;
        r1.v_start = v_mid;
      }
    }

    __forceinline unsigned int splitIntoSubRanges(GridRange r[4]) const
    {
      assert( !hasLeafSize() );
      unsigned int children = 0;
      GridRange first,second;
      split(first,second);

      if (first.hasLeafSize()) {
        r[0] = first;
        children++;
      } 
      else {
        first.split(r[0],r[1]);
        children += 2;
      }

      if (second.hasLeafSize())	{
        r[children] = second;
        children++;
      }
      else {
        second.split(r[children+0],r[children+1]);
        children += 2;
      }
      return children;      
    }
  };
}
