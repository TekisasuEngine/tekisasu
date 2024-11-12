/**************************************************************************/
/*  bvh_node_base.h                                                       */
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

#include "bvh_node_ref.h"

namespace embree
{
  
  /*! BVHN Base Node */
  template<typename NodeRef, int N>
    struct BaseNode_t
  {
    /*! Clears the node. */
    __forceinline void clear()
    {
      for (size_t i=0; i<N; i++)
        children[i] = NodeRef::emptyNode;
    }
    
    /*! Returns reference to specified child */
    __forceinline       NodeRef& child(size_t i)       { assert(i<N); return children[i]; }
    __forceinline const NodeRef& child(size_t i) const { assert(i<N); return children[i]; }
    
    /*! verifies the node */
    __forceinline bool verify() const
    {
      for (size_t i=0; i<N; i++) {
        if (child(i) == NodeRef::emptyNode) {
          for (; i<N; i++) {
            if (child(i) != NodeRef::emptyNode)
              return false;
          }
          break;
        }
      }
      return true;
    }
    
    NodeRef children[N];    //!< Pointer to the N children (can be a node or leaf)
  };
}
