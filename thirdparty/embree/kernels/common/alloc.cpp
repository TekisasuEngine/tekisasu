/**************************************************************************/
/*  alloc.cpp                                                             */
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

#include "alloc.h"
#include "../../common/sys/thread.h"
#if defined(APPLE) && defined(__aarch64__)
#include "../../common/sys/barrier.h"
#endif

namespace embree
{
  __thread FastAllocator::ThreadLocal2* FastAllocator::thread_local_allocator2 = nullptr;
  MutexSys FastAllocator::s_thread_local_allocators_lock;
  std::vector<std::unique_ptr<FastAllocator::ThreadLocal2>> FastAllocator::s_thread_local_allocators;
   
  struct fast_allocator_regression_test : public RegressionTest
  {
    BarrierSys barrier;
    std::atomic<size_t> numFailed;
    std::unique_ptr<FastAllocator> alloc;

    fast_allocator_regression_test() 
      : RegressionTest("fast_allocator_regression_test"), numFailed(0)
    {
      registerRegressionTest(this);
    }

    static void thread_alloc(fast_allocator_regression_test* This)
    {
      FastAllocator::CachedAllocator threadalloc = This->alloc->getCachedAllocator();

      size_t* ptrs[1000];
      for (size_t j=0; j<1000; j++)
      {
        This->barrier.wait();
        for (size_t i=0; i<1000; i++) {
          ptrs[i] = (size_t*) threadalloc.malloc0(sizeof(size_t)+(i%32));
          *ptrs[i] = size_t(threadalloc.talloc0) + i;
        }
        for (size_t i=0; i<1000; i++) {
          if (*ptrs[i] != size_t(threadalloc.talloc0) + i) 
            This->numFailed++;
        }
        This->barrier.wait();
      }
    }
    
    bool run ()
    {
      alloc = make_unique(new FastAllocator(nullptr,false));
      numFailed.store(0);

      size_t numThreads = getNumberOfLogicalThreads();
      barrier.init(numThreads+1);

      /* create threads */
      std::vector<thread_t> threads;
      for (size_t i=0; i<numThreads; i++)
        threads.push_back(createThread((thread_func)thread_alloc,this));

      /* run test */ 
      for (size_t i=0; i<1000; i++)
      {
        alloc->reset();
        barrier.wait();
        barrier.wait();
      }
     
      /* destroy threads */
      for (size_t i=0; i<numThreads; i++)
        join(threads[i]);

      alloc = nullptr;

      return numFailed == 0;
    }
  };

  fast_allocator_regression_test fast_allocator_regression;
}


