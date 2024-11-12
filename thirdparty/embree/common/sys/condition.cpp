/**************************************************************************/
/*  condition.cpp                                                         */
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

#include "condition.h"

#if defined(__WIN32__) && !defined(PTHREADS_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace embree
{
  struct ConditionImplementation
  {
    __forceinline ConditionImplementation () {
      InitializeConditionVariable(&cond);
    }

    __forceinline ~ConditionImplementation () {
    }

    __forceinline void wait(MutexSys& mutex_in) {
      SleepConditionVariableCS(&cond, (LPCRITICAL_SECTION)mutex_in.mutex, INFINITE);
    }

    __forceinline void notify_all() {
      WakeAllConditionVariable(&cond);
    }

  public:
    CONDITION_VARIABLE cond;
  };
}
#endif

#if defined(__UNIX__) || defined(PTHREADS_WIN32)
#include <pthread.h>
namespace embree
{
  struct ConditionImplementation
  {
    __forceinline ConditionImplementation () { 
      if (pthread_cond_init(&cond,nullptr) != 0)
        THROW_RUNTIME_ERROR("pthread_cond_init failed");
    }
    
    __forceinline ~ConditionImplementation() { 
      MAYBE_UNUSED bool ok = pthread_cond_destroy(&cond) == 0;
      assert(ok);
    }
    
    __forceinline void wait(MutexSys& mutex) { 
      if (pthread_cond_wait(&cond, (pthread_mutex_t*)mutex.mutex) != 0)
        THROW_RUNTIME_ERROR("pthread_cond_wait failed");
    }
    
    __forceinline void notify_all() { 
      if (pthread_cond_broadcast(&cond) != 0)
        THROW_RUNTIME_ERROR("pthread_cond_broadcast failed");
    }
    
  public:
    pthread_cond_t cond;
  };
}
#endif

namespace embree 
{
  ConditionSys::ConditionSys () { 
    cond = new ConditionImplementation; 
  }

  ConditionSys::~ConditionSys() { 
    delete (ConditionImplementation*) cond;
  }

  void ConditionSys::wait(MutexSys& mutex) { 
    ((ConditionImplementation*) cond)->wait(mutex);
  }

  void ConditionSys::notify_all() { 
    ((ConditionImplementation*) cond)->notify_all();
  }
}
