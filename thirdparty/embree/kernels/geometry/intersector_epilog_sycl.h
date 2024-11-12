/**************************************************************************/
/*  intersector_epilog_sycl.h                                             */
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

#include "../common/ray.h"
#include "../common/context.h"
#include "filter_sycl.h"

namespace embree
{
  template<typename Ray>
  struct Intersect1Epilog1_HWIF;

  template<>
  struct Intersect1Epilog1_HWIF<RayHit>
  {
    RayHit& ray;
    sycl::private_ptr<RayQueryContext> context;
    const unsigned int geomID;
    const unsigned int primID;
    const bool filter;
    
    __forceinline Intersect1Epilog1_HWIF(RayHit& ray,
                                         sycl::private_ptr<RayQueryContext> context,
                                         const unsigned int geomID,
                                         const unsigned int primID,
                                         const bool filter)
      : ray(ray), context(context), geomID(geomID), primID(primID), filter(filter) {}
    
    template<typename Hit_i>
    __forceinline bool operator() (Hit_i& hit_i) const
    {
      hit_i.finalize();

      Scene* scene MAYBE_UNUSED = context->scene;
      Geometry* geometry MAYBE_UNUSED = scene->get(geomID);

      /* ray mask test */
#if defined(EMBREE_RAY_MASK)
      if ((geometry->mask & ray.mask) == 0)
        return false;
#endif

      /* call intersection filter function */
#if defined(EMBREE_FILTER_FUNCTION) 
      if (filter && (unlikely(context->hasContextFilter() || geometry->hasIntersectionFilter())))
      {
        Hit h(context->user,geomID,primID,Vec2f(hit_i.u,hit_i.v),hit_i.Ng);
        float old_t = ray.tfar;
        ray.tfar = hit_i.t;
        bool found = runIntersectionFilter1SYCL(geometry,ray,context,h);
        if (!found) {
          ray.tfar = old_t;
          return false;
        }
      }
#endif
      
      ray.tfar = hit_i.t;
      ray.u = hit_i.u;
      ray.v = hit_i.v;
      ray.Ng.x = hit_i.Ng.x;
      ray.Ng.y = hit_i.Ng.y;
      ray.Ng.z = hit_i.Ng.z;
      ray.geomID = geomID;
      ray.primID = primID;
      instance_id_stack::copy_UU(context->user, context->user->instID, ray.instID);
#if defined(EMBREE_GEOMETRY_INSTANCE_ARRAY)
      instance_id_stack::copy_UU(context->user, context->user->instPrimID, ray.instPrimID);
#endif
      return true;
    }
    
    template<typename Hit_i>
    __forceinline bool operator() (bool, Hit_i& hit_i) const
    {
      hit_i.finalize();

      Scene* scene MAYBE_UNUSED = context->scene;
      Geometry* geometry MAYBE_UNUSED = scene->get(geomID);

      /* ray mask test */
#if defined(EMBREE_RAY_MASK)
      if ((geometry->mask & ray.mask) == 0)
        return false;
#endif

      const Vec3fa Ng = hit_i.Ng();
      const Vec2f uv = hit_i.uv();
      
      /* call intersection filter function */
#if defined(EMBREE_FILTER_FUNCTION) 
      if (filter && (unlikely(context->hasContextFilter() || geometry->hasIntersectionFilter())))
      {
        Hit h(context->user,geomID,primID,uv,Ng);
        float old_t = ray.tfar;
        ray.tfar = hit_i.t();
        bool found = runIntersectionFilter1SYCL(geometry,ray,context,h);
        if (!found) {
          ray.tfar = old_t;
          return false;
        }
      }
#endif
      
      ray.tfar = hit_i.t();
      ray.u = uv.x;
      ray.v = uv.y;
      ray.Ng.x = Ng.x;
      ray.Ng.y = Ng.y;
      ray.Ng.z = Ng.z;
      ray.geomID = geomID;
      ray.primID = primID;
      instance_id_stack::copy_UU(context->user, context->user->instID, ray.instID);
#if defined(EMBREE_GEOMETRY_INSTANCE_ARRAY)
      instance_id_stack::copy_UU(context->user, context->user->instPrimID, ray.instPrimID);
#endif
      return true;
    }
  };

  template<>
  struct Intersect1Epilog1_HWIF<Ray>
  {
    Ray& ray;
    sycl::private_ptr<RayQueryContext> context;
    const unsigned int geomID;
    const unsigned int primID;
    const bool filter;
    
    __forceinline Intersect1Epilog1_HWIF(Ray& ray,
                                         sycl::private_ptr<RayQueryContext> context,
                                         const unsigned int geomID,
                                         const unsigned int primID,
                                         const bool filter)
      : ray(ray), context(context), geomID(geomID), primID(primID), filter(filter) {}
    
    template<typename Hit_i>
    __forceinline bool operator() (Hit_i& hit_i) const
    {
      hit_i.finalize();

      Scene* scene MAYBE_UNUSED = context->scene;
      Geometry* geometry MAYBE_UNUSED = scene->get(geomID);

      /* ray mask test */
#if defined(EMBREE_RAY_MASK)
      if ((geometry->mask & ray.mask) == 0)
        return false;
#endif

      /* call intersection filter function */
#if defined(EMBREE_FILTER_FUNCTION) 
      if (filter && (unlikely(context->hasContextFilter() || geometry->hasOcclusionFilter())))
      {
        Hit h(context->user,geomID,primID,Vec2f(hit_i.u,hit_i.v),hit_i.Ng);
        float old_t = ray.tfar;
        ray.tfar = hit_i.t;
        bool found = runIntersectionFilter1SYCL(geometry,ray,context,h);
        if (!found) {
          ray.tfar = old_t;
          return false;
        }
      }
#endif
      
      ray.tfar = neg_inf;
      return true;
    }
    
    template<typename Hit_i>
    __forceinline bool operator() (bool, Hit_i& hit_i) const
    {
      hit_i.finalize();

      Scene* scene MAYBE_UNUSED = context->scene;
      Geometry* geometry MAYBE_UNUSED = scene->get(geomID);

      /* ray mask test */
#if defined(EMBREE_RAY_MASK)
      if ((geometry->mask & ray.mask) == 0)
        return false;
#endif

      /* call intersection filter function */
#if defined(EMBREE_FILTER_FUNCTION) 
      if (filter && (unlikely(context->hasContextFilter() || geometry->hasOcclusionFilter())))
      {
        const Vec3fa Ng = hit_i.Ng();
        const Vec2f uv = hit_i.uv();
        Hit h(context->user,geomID,primID,uv,Ng);
        float old_t = ray.tfar;
        ray.tfar = hit_i.t();
        bool found = runIntersectionFilter1SYCL(geometry,ray,context,h);
        if (!found) {
          ray.tfar = old_t;
          return false;
        }
      }
#endif
      
      ray.tfar = neg_inf;
      return true;
    }
  };
}
