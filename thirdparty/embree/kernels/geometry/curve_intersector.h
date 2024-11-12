/**************************************************************************/
/*  curve_intersector.h                                                   */
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
#include "../subdiv/bezier_curve.h"
#include "../common/primref.h"
#include "bezier_hair_intersector.h"
#include "bezier_ribbon_intersector.h"
#include "bezier_curve_intersector.h"
#include "oriented_curve_intersector.h"
#include "../bvh/node_intersector1.h"

// FIXME: this file seems replicate of curve_intersector_virtual.h

namespace embree
{
  namespace isa
  {
    struct VirtualCurveIntersector1
    {
      typedef unsigned char Primitive;
      typedef CurvePrecalculations1 Precalculations;
      
      template<int N, bool robust>
        static __forceinline void intersect(const Accel::Intersectors* This, Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive* prim, size_t num, const TravRay<N,robust> &tray, size_t& lazy_node)
      {
        assert(num == 1);
        RTCGeometryType ty = (RTCGeometryType)(*prim);
        assert(This->leafIntersector);
        VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
        leafIntersector.intersect<1>(&pre,&ray,context,prim);
      }
      
      template<int N, bool robust>        
        static __forceinline bool occluded(const Accel::Intersectors* This, Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive* prim, size_t num, const TravRay<N,robust> &tray, size_t& lazy_node)
      {
        assert(num == 1);
        RTCGeometryType ty = (RTCGeometryType)(*prim);
        assert(This->leafIntersector);
        VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
        return leafIntersector.occluded<1>(&pre,&ray,context,prim);
      }
    };

    template<int K>
      struct VirtualCurveIntersectorK 
      {
        typedef unsigned char Primitive;
        typedef CurvePrecalculationsK<K> Precalculations;
        
        static __forceinline void intersect(const vbool<K>& valid_i, const Accel::Intersectors* This, Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const Primitive* prim, size_t num, size_t& lazy_node)
        {
          assert(num == 1);
          RTCGeometryType ty = (RTCGeometryType)(*prim);
          assert(This->leafIntersector);
          VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
          size_t mask = movemask(valid_i);
          while (mask) leafIntersector.intersect<K>(&pre,&ray,bscf(mask),context,prim);
        }
        
        static __forceinline vbool<K> occluded(const vbool<K>& valid_i, const Accel::Intersectors* This, Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const Primitive* prim, size_t num, size_t& lazy_node)
        {
          assert(num == 1);
          RTCGeometryType ty = (RTCGeometryType)(*prim);
          assert(This->leafIntersector);
          VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
          vbool<K> valid_o = false;
          size_t mask = movemask(valid_i);
          while (mask) {
            size_t k = bscf(mask);
            if (leafIntersector.occluded<K>(&pre,&ray,k,context,prim))
              set(valid_o, k);
          }
          return valid_o;
        }
        
        static __forceinline void intersect(const Accel::Intersectors* This, Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const Primitive* prim, size_t num, size_t& lazy_node)
        {
          assert(num == 1);
          RTCGeometryType ty = (RTCGeometryType)(*prim);
          assert(This->leafIntersector);
          VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
          leafIntersector.intersect<K>(&pre,&ray,k,context,prim);
        }
        
        static __forceinline bool occluded(const Accel::Intersectors* This, Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const Primitive* prim, size_t num, size_t& lazy_node)
        {
          assert(num == 1);
          RTCGeometryType ty = (RTCGeometryType)(*prim);
          assert(This->leafIntersector);
          VirtualCurvePrimitive::Intersectors& leafIntersector = ((VirtualCurvePrimitive*) This->leafIntersector)->vtbl[ty];
          return leafIntersector.occluded<K>(&pre,&ray,k,context,prim);
        }
      };
  }
}
