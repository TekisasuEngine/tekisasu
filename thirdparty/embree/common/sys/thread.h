/**************************************************************************/
/*  thread.h                                                              */
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
#include "mutex.h"
#include "alloc.h"
#include "vector.h"
#include <vector>

namespace embree
{
  /*! type for thread */
  typedef struct opaque_thread_t* thread_t;

  /*! signature of thread start function */
  typedef void (*thread_func)(void*);

  /*! creates a hardware thread running on specific logical thread */
  thread_t createThread(thread_func f, void* arg, size_t stack_size = 0, ssize_t threadID = -1);

  /*! set affinity of the calling thread */
  void setAffinity(ssize_t affinity);

  /*! the thread calling this function gets yielded */
  void yield();

  /*! waits until the given thread has terminated */
  void join(thread_t tid);

  /*! destroy handle of a thread */
  void destroyThread(thread_t tid);

  /*! type for handle to thread local storage */
  typedef struct opaque_tls_t* tls_t;

  /*! creates thread local storage */
  tls_t createTls();

  /*! set the thread local storage pointer */
  void setTls(tls_t tls, void* const ptr);

  /*! return the thread local storage pointer */
  void* getTls(tls_t tls);

  /*! destroys thread local storage identifier */
  void destroyTls(tls_t tls);
}
