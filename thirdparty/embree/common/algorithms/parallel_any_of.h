/**************************************************************************/
/*  parallel_any_of.h                                                     */
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

#include <functional>
#include "parallel_reduce.h"

namespace embree
{
  
  template<typename Index, class UnaryPredicate>
    __forceinline bool parallel_any_of (Index first, Index last, UnaryPredicate pred)
  {
    std::atomic_bool ret;
    ret = false;
    
#if defined(TASKING_TBB)
#if TBB_INTERFACE_VERSION >= 12002
    tbb::task_group_context context;
    tbb::parallel_for(tbb::blocked_range<size_t>{first, last}, [&ret,pred,&context](const tbb::blocked_range<size_t>& r) {
        if (context.is_group_execution_cancelled()) return;
        for (size_t i = r.begin(); i != r.end(); ++i) {
          if (pred(i)) {
            ret = true;
            context.cancel_group_execution();
          }
        }
      });
#else
    tbb::parallel_for(tbb::blocked_range<size_t>{first, last}, [&ret,pred](const tbb::blocked_range<size_t>& r) {
        if (tbb::task::self().is_cancelled()) return;
        for (size_t i = r.begin(); i != r.end(); ++i) {
          if (pred(i)) {
            ret = true;
            tbb::task::self().cancel_group_execution();
          }
        }
      });
#endif
#else
    ret = parallel_reduce (first, last, false, [pred](const range<size_t>& r)->bool {
        bool localret = false;
        for (auto i=r.begin(); i<r.end(); ++i) {
          localret |= pred(i);
        }
        return localret;
      },
      std::bit_or<bool>()
      );
#endif
    
    return ret;
  }
  
} // end namespace
