/**************************************************************************/
/*  primitive.h                                                           */
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

#include "../common/default.h"
#include "../common/scene.h"
#include "../../common/simd/simd.h"
#include "../builders/primref.h"
#include "../builders/primref_mb.h"

namespace embree
{
  struct PrimitiveType
  {
    /*! returns name of this primitive type */
    virtual const char* name() const = 0;
    
    /*! Returns the number of stored active primitives in a block. */
    virtual size_t sizeActive(const char* This) const = 0;

    /*! Returns the number of stored active and inactive primitives in a block. */
    virtual size_t sizeTotal(const char* This) const = 0;

    /*! Returns the number of bytes of block. */
    virtual size_t getBytes(const char* This) const = 0;
  };
  
  template<typename Primitive>
  struct PrimitivePointQuery1
  {
    static __forceinline bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& prim)
    {
      bool changed = false;
      for (size_t i = 0; i < Primitive::max_size(); i++)
      {
        if (!prim.valid(i)) break;
        STAT3(point_query.trav_prims,1,1,1);
        AccelSet* accel = (AccelSet*)context->scene->get(prim.geomID(i));
        context->geomID = prim.geomID(i);
        context->primID = prim.primID(i);
        changed |= accel->pointQuery(query, context);
      }
      return changed;
    }
    
    static __forceinline void pointQueryNoop(PointQuery* query, PointQueryContext* context, const Primitive& prim) { }
  };
}
