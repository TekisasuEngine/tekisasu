/**************************************************************************/
/*  vector.h                                                              */
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

#include "default.h"

namespace embree
{
  /*! invokes the memory monitor callback */
  struct MemoryMonitorInterface {
    virtual void memoryMonitor(ssize_t bytes, bool post) = 0;
  };

  /*! allocator that performs aligned monitored allocations */
  template<typename T, size_t alignment = 64>
    struct aligned_monitored_allocator
    {
      typedef T value_type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef const T& const_reference;
      typedef std::size_t size_type;
      typedef std::ptrdiff_t difference_type;
      
      __forceinline aligned_monitored_allocator(MemoryMonitorInterface* device) 
        : device(device), hugepages(false) {}

      __forceinline pointer allocate( size_type n ) 
      {
        if (n) {
          assert(device);
          device->memoryMonitor(n*sizeof(T),false);
        }
        if (n*sizeof(value_type) >= 14 * PAGE_SIZE_2M)
        {
          pointer p =  (pointer) os_malloc(n*sizeof(value_type),hugepages);
          assert(p);
          return p;
        }
        return (pointer) alignedMalloc(n*sizeof(value_type),alignment);
      }

      __forceinline void deallocate( pointer p, size_type n ) 
      {
        if (p)
        {
          if (n*sizeof(value_type) >= 14 * PAGE_SIZE_2M)
            os_free(p,n*sizeof(value_type),hugepages); 
          else
            alignedFree(p);
        }
        else assert(n == 0);

        if (n) {
          assert(device);
          device->memoryMonitor(-ssize_t(n)*sizeof(T),true);
        }
      }

      __forceinline void construct( pointer p, const_reference val ) {
        new (p) T(val);
      }

      __forceinline void destroy( pointer p ) {
        p->~T();
      }

    private:
      MemoryMonitorInterface* device;
      bool hugepages;
    };

  /*! monitored vector */
  template<typename T>
    using mvector = vector_t<T,aligned_monitored_allocator<T,std::alignment_of<T>::value> >;
}
