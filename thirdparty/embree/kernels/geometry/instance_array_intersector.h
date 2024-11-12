/**************************************************************************/
/*  instance_array_intersector.h                                          */
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

#include "instance_array.h"
#include "../common/ray.h"
#include "../common/point_query.h"
#include "../common/scene.h"

namespace embree
{
  namespace isa
  {
    struct InstanceArrayIntersector1
    {
      typedef InstanceArrayPrimitive Primitive;

      struct Precalculations {
        __forceinline Precalculations (const Ray& ray, const void *ptr) {}
      };

      static void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& prim);
      static bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& prim);
      static bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& prim);
    };

    struct InstanceArrayIntersector1MB
    {
      typedef InstanceArrayPrimitive Primitive;

      struct Precalculations {
        __forceinline Precalculations (const Ray& ray, const void *ptr) {}
      };
      
      static void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& prim);
      static bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& prim);
      static bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& prim);
    };

    template<int K>
      struct InstanceArrayIntersectorK
    {
      typedef InstanceArrayPrimitive Primitive;
      
      struct Precalculations {
        __forceinline Precalculations (const vbool<K>& valid, const RayK<K>& ray) {}
      };
      
      static void intersect(const vbool<K>& valid_i, const Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const Primitive& prim);
      static vbool<K> occluded(const vbool<K>& valid_i, const Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const Primitive& prim);

      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const Primitive& prim) {
        intersect(vbool<K>(1<<int(k)),pre,ray,context,prim);
      }
      
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const Primitive& prim) {
        occluded(vbool<K>(1<<int(k)),pre,ray,context,prim);
        return ray.tfar[k] < 0.0f; 
      }
    };

    template<int K>
      struct InstanceArrayIntersectorKMB
    {
      typedef InstanceArrayPrimitive Primitive;
      
      struct Precalculations {
        __forceinline Precalculations (const vbool<K>& valid, const RayK<K>& ray) {}
      };
      
      static void intersect(const vbool<K>& valid_i, const Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const Primitive& prim);
      static vbool<K> occluded(const vbool<K>& valid_i, const Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const Primitive& prim);

      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const Primitive& prim) {
        intersect(vbool<K>(1<<int(k)),pre,ray,context,prim);
      }
      
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const Primitive& prim) {
        occluded(vbool<K>(1<<int(k)),pre,ray,context,prim);
        return ray.tfar[k] < 0.0f; 
      }
    };
  }
}
