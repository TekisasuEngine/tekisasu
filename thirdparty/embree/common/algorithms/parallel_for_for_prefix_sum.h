/**************************************************************************/
/*  parallel_for_for_prefix_sum.h                                         */
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

#include "parallel_for_for.h"
#include "parallel_prefix_sum.h"

namespace embree
{
  template<typename Value>
    struct ParallelForForPrefixSumState : public ParallelForForState
  {
    __forceinline ParallelForForPrefixSumState () {}

    template<typename ArrayArray>
      __forceinline ParallelForForPrefixSumState (ArrayArray& array2, const size_t minStepSize)
      : ParallelForForState(array2,minStepSize) {}

    template<typename SizeFunc>
    __forceinline ParallelForForPrefixSumState (size_t numArrays, const SizeFunc& getSize, const size_t minStepSize)
      : ParallelForForState(numArrays,getSize,minStepSize) {}

    ParallelPrefixSumState<Value> prefix_state;
  };
  
  template<typename SizeFunc, typename Index, typename Value, typename Func, typename Reduction>
    __forceinline Value parallel_for_for_prefix_sum0_( ParallelForForPrefixSumState<Value>& state, Index minStepSize, 
                                                       const SizeFunc& getSize, const Value& identity, const Func& func, const Reduction& reduction)
  {
    /* calculate number of tasks to use */
    const size_t taskCount = state.taskCount;
    
    /* perform parallel prefix sum */
    parallel_for(taskCount, [&](const size_t taskIndex)
    {
      const size_t k0 = (taskIndex+0)*state.size()/taskCount;
      const size_t k1 = (taskIndex+1)*state.size()/taskCount;
      size_t i0 = state.i0[taskIndex];
      size_t j0 = state.j0[taskIndex];

      /* iterate over arrays */
      size_t k=k0;
      Value N=identity;
      for (size_t i=i0; k<k1; i++) {
	const size_t size = getSize(i);
        const size_t r0 = j0, r1 = min(size,r0+k1-k);
        if (r1 > r0) N = reduction(N, func((Index)i,range<Index>((Index)r0,(Index)r1),(Index)k));
        k+=r1-r0; j0 = 0;
      }
      state.prefix_state.counts[taskIndex] = N;
    });

    /* calculate prefix sum */
    Value sum=identity;
    for (size_t i=0; i<taskCount; i++)
    {
      const Value c = state.prefix_state.counts[i];
      state.prefix_state.sums[i] = sum;
      sum=reduction(sum,c);
    }

    return sum;
  }

  template<typename SizeFunc, typename Index, typename Value, typename Func, typename Reduction>
    __forceinline Value parallel_for_for_prefix_sum1_( ParallelForForPrefixSumState<Value>& state, Index minStepSize, 
                                                       const SizeFunc& getSize, 
                                                       const Value& identity, const Func& func, const Reduction& reduction)
  {
    /* calculate number of tasks to use */
    const size_t taskCount = state.taskCount;
    /* perform parallel prefix sum */
    parallel_for(taskCount, [&](const size_t taskIndex)
    {
      const size_t k0 = (taskIndex+0)*state.size()/taskCount;
      const size_t k1 = (taskIndex+1)*state.size()/taskCount;
      size_t i0 = state.i0[taskIndex];
      size_t j0 = state.j0[taskIndex];

      /* iterate over arrays */
      size_t k=k0;
      Value N=identity;
      for (size_t i=i0; k<k1; i++) {
	const size_t size = getSize(i);
        const size_t r0 = j0, r1 = min(size,r0+k1-k);
        if (r1 > r0) N = reduction(N, func((Index)i,range<Index>((Index)r0,(Index)r1),(Index)k,reduction(state.prefix_state.sums[taskIndex],N)));
        k+=r1-r0; j0 = 0;
      }
      state.prefix_state.counts[taskIndex] = N;
    });

    /* calculate prefix sum */
    Value sum=identity;
    for (size_t i=0; i<taskCount; i++)
    {
      const Value c = state.prefix_state.counts[i];
      state.prefix_state.sums[i] = sum;
      sum=reduction(sum,c);
    }

    return sum;
  }

  template<typename ArrayArray, typename Index, typename Value, typename Func, typename Reduction>
  __forceinline Value parallel_for_for_prefix_sum0( ParallelForForPrefixSumState<Value>& state,
                                                    ArrayArray& array2, Index minStepSize, 
                                                    const Value& identity, const Func& func, const Reduction& reduction)
  {
    return parallel_for_for_prefix_sum0_(state,minStepSize,
                                        [&](Index i) { return array2[i] ? array2[i]->size() : 0; },
                                        identity,
                                        [&](Index i, const range<Index>& r, Index k) { return func(array2[i], r, k, i); },
                                        reduction);
  }

  template<typename ArrayArray, typename Index, typename Value, typename Func, typename Reduction>
  __forceinline Value parallel_for_for_prefix_sum1( ParallelForForPrefixSumState<Value>& state,
                                                    ArrayArray& array2, Index minStepSize, 
                                                    const Value& identity, const Func& func, const Reduction& reduction)
  {
    return parallel_for_for_prefix_sum1_(state,minStepSize,
                                        [&](Index i) { return array2[i] ? array2[i]->size() : 0; },
                                        identity,
                                        [&](Index i, const range<Index>& r, Index k, const Value& base) { return func(array2[i], r, k, i, base); },
                                        reduction);
  }                                       

  template<typename ArrayArray, typename Value, typename Func, typename Reduction>
    __forceinline Value parallel_for_for_prefix_sum0( ParallelForForPrefixSumState<Value>& state, ArrayArray& array2, 
						     const Value& identity, const Func& func, const Reduction& reduction)
  {
    return parallel_for_for_prefix_sum0(state,array2,size_t(1),identity,func,reduction);
  }

  template<typename ArrayArray, typename Value, typename Func, typename Reduction>
    __forceinline Value parallel_for_for_prefix_sum1( ParallelForForPrefixSumState<Value>& state, ArrayArray& array2, 
						     const Value& identity, const Func& func, const Reduction& reduction)
  {
    return parallel_for_for_prefix_sum1(state,array2,size_t(1),identity,func,reduction);
  }
}
