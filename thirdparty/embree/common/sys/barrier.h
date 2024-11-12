/**************************************************************************/
/*  barrier.h                                                             */
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

#include "intrinsics.h"
#include "sysinfo.h"
#include "atomic.h"

namespace embree
{
  /*! system barrier using operating system */
  class BarrierSys
  {
  public:

    /*! construction / destruction */
    BarrierSys (size_t N = 0);
    ~BarrierSys ();

  private:
    /*! class in non-copyable */
    BarrierSys (const BarrierSys& other) DELETED; // do not implement
    BarrierSys& operator= (const BarrierSys& other) DELETED; // do not implement

  public:
    /*! initializes the barrier with some number of threads */
    void init(size_t count);

    /*! lets calling thread wait in barrier */
    void wait();

  private:
    void* opaque;
  };

  /*! fast active barrier using atomic counter */
  struct BarrierActive 
  {
  public:
    BarrierActive () 
      : cntr(0) {}
    
    void reset() {
      cntr.store(0);
    }

    void wait (size_t numThreads) 
    {
      cntr++;
      while (cntr.load() != numThreads) 
        pause_cpu();
    }

  private:
    std::atomic<size_t> cntr;
  };

  /*! fast active barrier that does not require initialization to some number of threads */
  struct BarrierActiveAutoReset
  {
  public:
    BarrierActiveAutoReset () 
      : cntr0(0), cntr1(0) {}

    void wait (size_t threadCount) 
    {
      cntr0.fetch_add(1);
      while (cntr0 != threadCount) pause_cpu();
      cntr1.fetch_add(1);
      while (cntr1 != threadCount) pause_cpu();
      cntr0.fetch_add(-1);
      while (cntr0 != 0) pause_cpu();
      cntr1.fetch_add(-1);
      while (cntr1 != 0) pause_cpu();
    }

  private:
    std::atomic<size_t> cntr0;
    std::atomic<size_t> cntr1;
  };

  class LinearBarrierActive
  {
  public:

    /*! construction and destruction */
    LinearBarrierActive (size_t threadCount = 0);
    ~LinearBarrierActive();
    
  private:
    /*! class in non-copyable */
    LinearBarrierActive (const LinearBarrierActive& other) DELETED; // do not implement
    LinearBarrierActive& operator= (const LinearBarrierActive& other) DELETED; // do not implement

  public:
    /*! initializes the barrier with some number of threads */
    void init(size_t threadCount);
    
    /*! thread with threadIndex waits in the barrier */
    void wait (const size_t threadIndex);
    
  private:
    volatile unsigned char* count0;
    volatile unsigned char* count1; 
    volatile unsigned int mode;
    volatile unsigned int flag0;
    volatile unsigned int flag1;
    volatile size_t threadCount;
  };
}

