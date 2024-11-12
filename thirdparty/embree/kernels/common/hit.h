/**************************************************************************/
/*  hit.h                                                                 */
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

#include "default.h"
#include "ray.h"
#include "instance_stack.h"

namespace embree
{
  /* Hit structure for K hits */
  template<int K>
    struct HitK
  {
    /* Default construction does nothing */
    __forceinline HitK() {}

    /* Constructs a hit */
    __forceinline HitK(const RTCRayQueryContext* context, const vuint<K>& geomID, const vuint<K>& primID, const vfloat<K>& u, const vfloat<K>& v, const Vec3vf<K>& Ng)
      : Ng(Ng), u(u), v(v), primID(primID), geomID(geomID) 
    {
      for (unsigned l = 0; l < RTC_MAX_INSTANCE_LEVEL_COUNT; ++l) {
        instID[l] = RTC_INVALID_GEOMETRY_ID;
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
        instPrimID[l] = RTC_INVALID_GEOMETRY_ID;
#endif
      }
      
      instance_id_stack::copy_UV<K>(context->instID, instID);
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
      instance_id_stack::copy_UV<K>(context->instPrimID, instPrimID);
#endif
    }

    /* Constructs a hit */
    __forceinline HitK(const RTCRayQueryContext* context, const vuint<K>& geomID, const vuint<K>& primID, const Vec2vf<K>& uv, const Vec3vf<K>& Ng)
      : HitK(context,geomID,primID,uv.x,uv.y,Ng) {}

    /* Returns the size of the hit */
    static __forceinline size_t size() { return K; }

  public:
    Vec3vf<K> Ng;  // geometry normal
    vfloat<K> u;         // barycentric u coordinate of hit
    vfloat<K> v;         // barycentric v coordinate of hit
    vuint<K> primID;      // primitive ID
    vuint<K> geomID;      // geometry ID
    vuint<K> instID[RTC_MAX_INSTANCE_LEVEL_COUNT];      // instance ID
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
    vuint<K> instPrimID[RTC_MAX_INSTANCE_LEVEL_COUNT];      // instance primitive ID
#endif
  };

  /* Specialization for a single hit */
  template<>
    struct __aligned(16) HitK<1>
  {
     /* Default construction does nothing */
    __forceinline HitK() {}

    /* Constructs a hit */
    __forceinline HitK(const RTCRayQueryContext* context, unsigned int geomID, unsigned int primID, float u, float v, const Vec3fa& Ng)
      : Ng(Ng.x,Ng.y,Ng.z), u(u), v(v), primID(primID), geomID(geomID)
    {
      instance_id_stack::copy_UU(context, context->instID, instID);
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
      instance_id_stack::copy_UU(context, context->instPrimID, instPrimID);
#endif
    }

    /* Constructs a hit */
    __forceinline HitK(const RTCRayQueryContext* context, unsigned int geomID, unsigned int primID, const Vec2f& uv, const Vec3fa& Ng)
      : HitK<1>(context,geomID,primID,uv.x,uv.y,Ng) {}

    /* Returns the size of the hit */
    static __forceinline size_t size() { return 1; }

  public:
    Vec3<float> Ng;  // geometry normal
    float u;         // barycentric u coordinate of hit
    float v;         // barycentric v coordinate of hit
    unsigned int primID;      // primitive ID
    unsigned int geomID;      // geometry ID
    unsigned int instID[RTC_MAX_INSTANCE_LEVEL_COUNT];      // instance ID
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
    unsigned int instPrimID[RTC_MAX_INSTANCE_LEVEL_COUNT];      // instance primitive ID
#endif
  };

  /* Shortcuts */
  typedef HitK<1>  Hit;
  typedef HitK<4>  Hit4;
  typedef HitK<8>  Hit8;
  typedef HitK<16> Hit16;
  typedef HitK<VSIZEX> Hitx;

  /* Outputs hit to stream */
  template<int K>
  __forceinline embree_ostream operator<<(embree_ostream cout, const HitK<K>& ray)
  {
    cout << "{ " << embree_endl
         << "  Ng = " << ray.Ng <<  embree_endl
         << "  u = " << ray.u <<  embree_endl
         << "  v = " << ray.v << embree_endl
         << "  primID = " << ray.primID <<  embree_endl
         << "  geomID = " << ray.geomID << embree_endl
         << "  instID =";
    for (unsigned l = 0; l < RTC_MAX_INSTANCE_LEVEL_COUNT; ++l)
    {
      cout << " " << ray.instID[l];
    }
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
    cout << "  instPrimID =";
    for (unsigned l = 0; l < RTC_MAX_INSTANCE_LEVEL_COUNT; ++l)
    {
      cout << " " << ray.instPrimID[l];
    }
#endif
    cout << embree_endl;
    return cout << "}";
  }

  template<typename Hit>
    __forceinline void copyHitToRay(RayHit& ray, const Hit& hit)
  {
    ray.Ng   = hit.Ng;
    ray.u    = hit.u;
    ray.v    = hit.v;
    ray.primID = hit.primID;
    ray.geomID = hit.geomID;
    instance_id_stack::copy_UU(hit.instID, ray.instID);
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
    instance_id_stack::copy_UU(hit.instPrimID, ray.instPrimID);
#endif
  }

  template<int K>
    __forceinline void copyHitToRay(const vbool<K>& mask, RayHitK<K>& ray, const HitK<K>& hit)
  {
    vfloat<K>::storeu(mask,&ray.Ng.x, hit.Ng.x);
    vfloat<K>::storeu(mask,&ray.Ng.y, hit.Ng.y);
    vfloat<K>::storeu(mask,&ray.Ng.z, hit.Ng.z);
    vfloat<K>::storeu(mask,&ray.u, hit.u);
    vfloat<K>::storeu(mask,&ray.v, hit.v);
    vuint<K>::storeu(mask,&ray.primID, hit.primID);
    vuint<K>::storeu(mask,&ray.geomID, hit.geomID);
    instance_id_stack::copy_VV<K>(hit.instID, ray.instID, mask);
#if defined(RTC_GEOMETRY_INSTANCE_ARRAY)
    instance_id_stack::copy_VV<K>(hit.instPrimID, ray.instPrimID, mask);
#endif
  }
}
