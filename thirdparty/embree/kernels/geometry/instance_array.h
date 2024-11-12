/**************************************************************************/
/*  instance_array.h                                                      */
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

#include "primitive.h"
#include "../common/scene_instance_array.h"

namespace embree
{
  //template<int M>
  struct InstanceArrayPrimitive
  {
    struct Type : public PrimitiveType
    {
      const char* name() const;
      size_t sizeActive(const char* This) const;
      size_t sizeTotal(const char* This) const;
      size_t getBytes(const char* This) const;
    };
    static Type type;

  public:

    /* primitive supports multiple time segments */
    static const bool singleTimeSegment = false;

    /* Returns maximum number of stored primitives */
    static __forceinline size_t max_size() { return 1; }

    /* Returns required number of primitive blocks for N primitives */
    static __forceinline size_t blocks(size_t N) { return N; }

  public:

    InstanceArrayPrimitive (const uint32_t geomID, const uint32_t primID)
    : primID_(primID)
    , instID_(geomID)
    {}

    __forceinline bool valid() const { 
      return primID_ != -1;
    }

    void fill(const PrimRef* prims, size_t& i, size_t end, Scene* scene)
    {
      assert(end-i == 1);
      const PrimRef& prim = prims[i]; i++;
      const unsigned int geomID = prim.geomID();
      const unsigned int primID = prim.primID();
      new (this) InstanceArrayPrimitive(geomID, primID);
    }

    __forceinline LBBox3fa fillMB(const PrimRef* prims, size_t& i, size_t end, Scene* scene, size_t itime)
    {
      assert(end-i == 1);
      const PrimRef& prim = prims[i]; i++;
      const unsigned int geomID = prim.geomID();
      const size_t primID = prim.primID();
      new (this) InstanceArrayPrimitive(geomID, primID);
      const InstanceArray* instanceArray = scene->get<InstanceArray>(geomID);
      return instanceArray->linearBounds(primID,itime);
    }

    __forceinline LBBox3fa fillMB(const PrimRefMB* prims, size_t& i, size_t end, Scene* scene, const BBox1f time_range)
    {
      assert(end-i == 1);
      const PrimRefMB& prim = prims[i]; i++;
      const unsigned int geomID = prim.geomID();
      const size_t primID = prim.primID();
      new (this) InstanceArrayPrimitive(geomID, primID);
      const InstanceArray* instanceArray = scene->get<InstanceArray>(geomID);
      return instanceArray->linearBounds(primID,time_range);
    }

    /* Updates the primitive */
    __forceinline BBox3fa update(InstanceArray* instanceArray) {
      return instanceArray->bounds(0);
    }

  public:
    unsigned int primID_;
    unsigned int instID_;
  };
}
