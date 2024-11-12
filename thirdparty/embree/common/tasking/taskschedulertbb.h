/**************************************************************************/
/*  taskschedulertbb.h                                                    */
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

#include "../sys/platform.h"
#include "../sys/alloc.h"
#include "../sys/barrier.h"
#include "../sys/thread.h"
#include "../sys/mutex.h"
#include "../sys/condition.h"
#include "../sys/ref.h"

#if defined(__WIN32__) && !defined(NOMINMAX)
#  define NOMINMAX
#endif

#if defined(__INTEL_LLVM_COMPILER)
// prevents "'__thiscall' calling convention is not supported for this target" warning from TBB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"
#endif

// We need to define these to avoid implicit linkage against
// tbb_debug.lib under Windows. When removing these lines debug build
// under Windows fails.
#define __TBB_NO_IMPLICIT_LINKAGE 1
#define __TBBMALLOC_NO_IMPLICIT_LINKAGE 1
#define TBB_SUPPRESS_DEPRECATED_MESSAGES 1
#define TBB_PREVIEW_ISOLATED_TASK_GROUP 1
#include "tbb/tbb.h"
#include "tbb/parallel_sort.h"

#if defined(TASKING_TBB) && (TBB_INTERFACE_VERSION_MAJOR >= 8)
#  define USE_TASK_ARENA 1
#else
#  define USE_TASK_ARENA 0
#endif

#if defined(TASKING_TBB) && (TBB_INTERFACE_VERSION >= 11009) // TBB 2019 Update 9
#  define TASKING_TBB_USE_TASK_ISOLATION 1
#else
#  define TASKING_TBB_USE_TASK_ISOLATION 0
#endif

namespace embree
{
  struct TaskScheduler
  {
    /*! initializes the task scheduler */
    static void create(size_t numThreads, bool set_affinity, bool start_threads);

    /*! destroys the task scheduler again */
    static void destroy();

    /* returns the ID of the current thread */
    static __forceinline size_t threadID()
    {
      return threadIndex();
    }

    /* returns the index (0..threadCount-1) of the current thread */
    static __forceinline size_t threadIndex()
    {
#if TBB_INTERFACE_VERSION >= 9100
      return tbb::this_task_arena::current_thread_index();
#elif TBB_INTERFACE_VERSION >= 9000
      return tbb::task_arena::current_thread_index();
#else
      return 0;
#endif
    }

    /* returns the total number of threads */
    static __forceinline size_t threadCount() {
#if TBB_INTERFACE_VERSION >= 9100
      return tbb::this_task_arena::max_concurrency();
#else
      return tbb::task_scheduler_init::default_num_threads();
#endif
    }

  };

};

#if defined(__INTEL_LLVM_COMPILER)
#pragma clang diagnostic pop
#endif