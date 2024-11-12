/**************************************************************************/
/*  atomic.h                                                              */
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

#include <atomic>
#include "intrinsics.h"

namespace embree
{
/* compiler memory barriers */
#if defined(__INTEL_COMPILER)
//#define __memory_barrier() __memory_barrier()
#elif defined(__GNUC__) || defined(__clang__)
#  define __memory_barrier() asm volatile("" ::: "memory")
#elif  defined(_MSC_VER)
#  define __memory_barrier() _ReadWriteBarrier()
#endif

  template <typename T>
    struct atomic : public std::atomic<T>
  {
    atomic () {}
      
    atomic (const T& a)
      : std::atomic<T>(a) {}

    atomic (const atomic<T>& a) {
      this->store(a.load());
    }

    atomic& operator=(const atomic<T>& other) {
      this->store(other.load());
      return *this;
    }
  };

  template<typename T>
    __forceinline void _atomic_min(std::atomic<T>& aref, const T& bref)
  {
    const T b = bref.load();
    while (true) {
      T a = aref.load();
      if (a <= b) break;
      if (aref.compare_exchange_strong(a,b)) break;
    }
  }

  template<typename T>
    __forceinline void _atomic_max(std::atomic<T>& aref, const T& bref)
  {
    const T b = bref.load();
    while (true) {
      T a = aref.load();
      if (a >= b) break;
      if (aref.compare_exchange_strong(a,b)) break;
    }
  }
}
