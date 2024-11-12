/**************************************************************************/
/*  curveNv_intersector.h                                                 */
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

#include "curveNv.h"
#include "curveNi_intersector.h"

namespace embree
{
  namespace isa
  {
    template<int M>
      struct CurveNvIntersector1 : public CurveNiIntersector1<M>
    {
      typedef CurveNv<M> Primitive;
      typedef CurvePrecalculations1 Precalculations;

      template<typename Intersector, typename Epilog>
        static __forceinline void intersect_t(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& prim)
      {
        vfloat<M> tNear;
        vbool<M> valid = CurveNiIntersector1<M>::intersect(ray,prim,tNear);

        const size_t N = prim.N;
        size_t mask = movemask(valid);
        while (mask)
        {
          const size_t i = bscf(mask);
          STAT3(normal.trav_prims,1,1,1);
          const unsigned int geomID = prim.geomID(N);
          const unsigned int primID = prim.primID(N)[i];
          const CurveGeometry* geom = (CurveGeometry*) context->scene->get(geomID);
          const Vec3ff a0 = Vec3ff::loadu(&prim.vertices(i,N)[0]);
          const Vec3ff a1 = Vec3ff::loadu(&prim.vertices(i,N)[1]);
          const Vec3ff a2 = Vec3ff::loadu(&prim.vertices(i,N)[2]);
          const Vec3ff a3 = Vec3ff::loadu(&prim.vertices(i,N)[3]);

          size_t mask1 = mask;
          const size_t i1 = bscf(mask1);
          if (mask) {
            prefetchL1(&prim.vertices(i1,N)[0]);
            prefetchL1(&prim.vertices(i1,N)[4]);
            if (mask1) {
              const size_t i2 = bsf(mask1);
              prefetchL2(&prim.vertices(i2,N)[0]);
              prefetchL2(&prim.vertices(i2,N)[4]);
            }
          }

          Intersector().intersect(pre,ray,context,geom,primID,a0,a1,a2,a3,Epilog(ray,context,geomID,primID));
          mask &= movemask(tNear <= vfloat<M>(ray.tfar));
        }
      }

      template<typename Intersector, typename Epilog>
        static __forceinline bool occluded_t(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& prim)
      {
        vfloat<M> tNear;
        vbool<M> valid = CurveNiIntersector1<M>::intersect(ray,prim,tNear);

        const size_t N = prim.N;
        size_t mask = movemask(valid);
        while (mask)
        {
          const size_t i = bscf(mask);
          STAT3(shadow.trav_prims,1,1,1);
          const unsigned int geomID = prim.geomID(N);
          const unsigned int primID = prim.primID(N)[i];
          const CurveGeometry* geom = (CurveGeometry*) context->scene->get(geomID);
          const Vec3ff a0 = Vec3ff::loadu(&prim.vertices(i,N)[0]);
          const Vec3ff a1 = Vec3ff::loadu(&prim.vertices(i,N)[1]);
          const Vec3ff a2 = Vec3ff::loadu(&prim.vertices(i,N)[2]);
          const Vec3ff a3 = Vec3ff::loadu(&prim.vertices(i,N)[3]);

          size_t mask1 = mask;
          const size_t i1 = bscf(mask1);
          if (mask) {
            prefetchL1(&prim.vertices(i1,N)[0]);
            prefetchL1(&prim.vertices(i1,N)[4]);
            if (mask1) {
              const size_t i2 = bsf(mask1);
              prefetchL2(&prim.vertices(i2,N)[0]);
              prefetchL2(&prim.vertices(i2,N)[4]);
            }
          }
          
          if (Intersector().intersect(pre,ray,context,geom,primID,a0,a1,a2,a3,Epilog(ray,context,geomID,primID)))
            return true;
          
          mask &= movemask(tNear <= vfloat<M>(ray.tfar));
        }
        return false;
      }
    };

    template<int M, int K>
      struct CurveNvIntersectorK : public CurveNiIntersectorK<M,K>
    {
      typedef CurveNv<M> Primitive;
      typedef CurvePrecalculationsK<K> Precalculations;

      template<typename Intersector, typename Epilog>
        static __forceinline void intersect_t(Precalculations& pre, RayHitK<K>& ray, const size_t k, RayQueryContext* context, const Primitive& prim)
      {
        vfloat<M> tNear;
        vbool<M> valid = CurveNiIntersectorK<M,K>::intersect(ray,k,prim,tNear);

        const size_t N = prim.N;
        size_t mask = movemask(valid);
        while (mask)
        {
          const size_t i = bscf(mask);
          STAT3(normal.trav_prims,1,1,1);
          const unsigned int geomID = prim.geomID(N);
          const unsigned int primID = prim.primID(N)[i];
          const CurveGeometry* geom = (CurveGeometry*) context->scene->get(geomID);
          const Vec3ff a0 = Vec3ff::loadu(&prim.vertices(i,N)[0]);
          const Vec3ff a1 = Vec3ff::loadu(&prim.vertices(i,N)[1]);
          const Vec3ff a2 = Vec3ff::loadu(&prim.vertices(i,N)[2]);
          const Vec3ff a3 = Vec3ff::loadu(&prim.vertices(i,N)[3]);

          size_t mask1 = mask;
          const size_t i1 = bscf(mask1);
          if (mask) {
            prefetchL1(&prim.vertices(i1,N)[0]);
            prefetchL1(&prim.vertices(i1,N)[4]);
            if (mask1) {
              const size_t i2 = bsf(mask1);
              prefetchL2(&prim.vertices(i2,N)[0]);
              prefetchL2(&prim.vertices(i2,N)[4]);
            }
          }

          Intersector().intersect(pre,ray,k,context,geom,primID,a0,a1,a2,a3,Epilog(ray,k,context,geomID,primID));
          mask &= movemask(tNear <= vfloat<M>(ray.tfar[k]));
        }
      }

      template<typename Intersector, typename Epilog>
        static __forceinline bool occluded_t(Precalculations& pre, RayK<K>& ray, const size_t k, RayQueryContext* context, const Primitive& prim)
      {
        vfloat<M> tNear;
        vbool<M> valid = CurveNiIntersectorK<M,K>::intersect(ray,k,prim,tNear);

        const size_t N = prim.N;
        size_t mask = movemask(valid);
        while (mask)
        {
          const size_t i = bscf(mask);
          STAT3(shadow.trav_prims,1,1,1);
          const unsigned int geomID = prim.geomID(N);
          const unsigned int primID = prim.primID(N)[i];
          const CurveGeometry* geom = (CurveGeometry*) context->scene->get(geomID);
          const Vec3ff a0 = Vec3ff::loadu(&prim.vertices(i,N)[0]);
          const Vec3ff a1 = Vec3ff::loadu(&prim.vertices(i,N)[1]);
          const Vec3ff a2 = Vec3ff::loadu(&prim.vertices(i,N)[2]);
          const Vec3ff a3 = Vec3ff::loadu(&prim.vertices(i,N)[3]);

          size_t mask1 = mask;
          const size_t i1 = bscf(mask1);
          if (mask) {
            prefetchL1(&prim.vertices(i1,N)[0]);
            prefetchL1(&prim.vertices(i1,N)[4]);
            if (mask1) {
              const size_t i2 = bsf(mask1);
              prefetchL2(&prim.vertices(i2,N)[0]);
              prefetchL2(&prim.vertices(i2,N)[4]);
            }
          }

          if (Intersector().intersect(pre,ray,k,context,geom,primID,a0,a1,a2,a3,Epilog(ray,k,context,geomID,primID)))
            return true;

          mask &= movemask(tNear <= vfloat<M>(ray.tfar[k]));
        }
        return false;
      }
    };
  }
}
