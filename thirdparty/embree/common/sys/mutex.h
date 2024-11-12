/**************************************************************************/
/*  mutex.h                                                               */
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

#include "platform.h"
#include "intrinsics.h"
#include "atomic.h"

#define CPU_CACHELINE_SIZE 64
namespace embree
{
  /*! system mutex */
  class MutexSys {
    friend struct ConditionImplementation;
  public:
    MutexSys();
    ~MutexSys();

  private:
    MutexSys (const MutexSys& other) DELETED; // do not implement
    MutexSys& operator= (const MutexSys& other) DELETED; // do not implement

  public:
    void lock();
    bool try_lock();
    void unlock();

  protected:
    void* mutex;
  };

  /*! spinning mutex */
  class SpinLock
  {
  public:
 
    SpinLock ()
      : flag(false) {}

    __forceinline bool isLocked() {
      return flag.load();
    }

    __forceinline void lock()
    {
      while (true) 
      {
        while (flag.load()) 
        {
          _mm_pause(); 
          _mm_pause();
        }
        
        bool expected = false;
        if (flag.compare_exchange_strong(expected,true,std::memory_order_acquire))
          break;
      }
    }
    
    __forceinline bool try_lock()
    {
      bool expected = false;
      if (flag.load() != expected) {
        return false;
      }
      return flag.compare_exchange_strong(expected,true,std::memory_order_acquire);
    }

    __forceinline void unlock() {
      flag.store(false,std::memory_order_release);
    }
    
    __forceinline void wait_until_unlocked() 
    {
      while(flag.load())
      {
        _mm_pause(); 
        _mm_pause();
      }
    }

  public:
    atomic<bool> flag;
  };

  class PaddedSpinLock : public SpinLock
  {
  private:
    MAYBE_UNUSED char padding[CPU_CACHELINE_SIZE - sizeof(SpinLock)];
  };
  /*! safe mutex lock and unlock helper */
  template<typename Mutex> class Lock {
  public:
    Lock (Mutex& mutex) : mutex(mutex), locked(true) { mutex.lock(); }
    Lock (Mutex& mutex, bool locked) : mutex(mutex), locked(locked) {}
    ~Lock() { if (locked) mutex.unlock(); }
    __forceinline void lock() { assert(!locked); locked = true; mutex.lock(); }
    __forceinline bool isLocked() const { return locked; }
  protected:
    Mutex& mutex;
    bool locked;
  };
}
