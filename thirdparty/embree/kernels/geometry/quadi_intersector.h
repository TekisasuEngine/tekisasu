/**************************************************************************/
/*  quadi_intersector.h                                                   */
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

#include "quadi.h"
#include "quad_intersector_moeller.h"
#include "quad_intersector_pluecker.h"

namespace embree
{
  namespace isa
  {
    /*! Intersects M quads with 1 ray */
    template<int M, bool filter>
    struct QuadMiIntersector1Moeller
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersector1MoellerTrumbore<M,filter> Precalculations;

      /*! Intersect a ray with the M quads and updates the hit. */
      static __forceinline void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        pre.intersect(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of M quads. */
      static __forceinline bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        return pre.occluded(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      static __forceinline bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& quad)
      {
        return PrimitivePointQuery1<Primitive>::pointQuery(query, context, quad);
      }
    };

    /*! Intersects M triangles with K rays. */
    template<int M, int K, bool filter>
    struct QuadMiIntersectorKMoeller
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersectorKMoellerTrumbore<M,K,filter> Precalculations;

      /*! Intersects K rays with M triangles. */
      static __forceinline void intersect(const vbool<K>& valid_i, Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        Scene* scene = context->scene;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(normal.trav_prims,1,popcnt(valid_i),K);
          const Vec3vf<K> p0 = quad.template getVertex<0>(i,scene);
          const Vec3vf<K> p1 = quad.template getVertex<1>(i,scene);
          const Vec3vf<K> p2 = quad.template getVertex<2>(i,scene);
          const Vec3vf<K> p3 = quad.template getVertex<3>(i,scene);
          pre.intersectK(valid_i,ray,p0,p1,p2,p3,IntersectKEpilogM<M,K,filter>(ray,context,quad.geomID(),quad.primID(),i));
        }
      }

      /*! Test for K rays if they are occluded by any of the M triangles. */
      static __forceinline vbool<K> occluded(const vbool<K>& valid_i, Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        Scene* scene = context->scene;
        vbool<K> valid0 = valid_i;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(shadow.trav_prims,1,popcnt(valid0),K);
          const Vec3vf<K> p0 = quad.template getVertex<0>(i,scene);
          const Vec3vf<K> p1 = quad.template getVertex<1>(i,scene);
          const Vec3vf<K> p2 = quad.template getVertex<2>(i,scene);
          const Vec3vf<K> p3 = quad.template getVertex<3>(i,scene);
          if (pre.intersectK(valid0,ray,p0,p1,p2,p3,OccludedKEpilogM<M,K,filter>(valid0,ray,context,quad.geomID(),quad.primID(),i)))
            break;
        }
        return !valid0;
      }
      
      /*! Intersect a ray with M triangles and updates the hit. */
      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf4 v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        pre.intersect1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of the M triangles. */
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf4 v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        return pre.occluded1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
    };

    /*! Intersects M quads with 1 ray */
    template<int M, bool filter>
    struct QuadMiIntersector1Pluecker
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersector1Pluecker<M,filter> Precalculations;

      /*! Intersect a ray with the M quads and updates the hit. */
      static __forceinline void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        pre.intersect(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of M quads. */
      static __forceinline bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        return pre.occluded(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
      
      static __forceinline bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& quad)
      {
        return PrimitivePointQuery1<Primitive>::pointQuery(query, context, quad);
      }
    };

    /*! Intersects M triangles with K rays. */
    template<int M, int K, bool filter>
    struct QuadMiIntersectorKPluecker
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersectorKPluecker<M,K,filter> Precalculations;

      /*! Intersects K rays with M triangles. */
      static __forceinline void intersect(const vbool<K>& valid_i, Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        Scene* scene = context->scene;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(normal.trav_prims,1,popcnt(valid_i),K);
          const Vec3vf<K> p0 = quad.template getVertex<0>(i,scene);
          const Vec3vf<K> p1 = quad.template getVertex<1>(i,scene);
          const Vec3vf<K> p2 = quad.template getVertex<2>(i,scene);
          const Vec3vf<K> p3 = quad.template getVertex<3>(i,scene);
          pre.intersectK(valid_i,ray,p0,p1,p2,p3,IntersectKEpilogM<M,K,filter>(ray,context,quad.geomID(),quad.primID(),i));
        }
      }

      /*! Test for K rays if they are occluded by any of the M triangles. */
      static __forceinline vbool<K> occluded(const vbool<K>& valid_i, Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        Scene* scene = context->scene;
        vbool<K> valid0 = valid_i;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(shadow.trav_prims,1,popcnt(valid0),K);
          const Vec3vf<K> p0 = quad.template getVertex<0>(i,scene);
          const Vec3vf<K> p1 = quad.template getVertex<1>(i,scene);
          const Vec3vf<K> p2 = quad.template getVertex<2>(i,scene);
          const Vec3vf<K> p3 = quad.template getVertex<3>(i,scene);
          if (pre.intersectK(valid0,ray,p0,p1,p2,p3,OccludedKEpilogM<M,K,filter>(valid0,ray,context,quad.geomID(),quad.primID(),i)))
            break;
        }
        return !valid0;
      }
      
      /*! Intersect a ray with M triangles and updates the hit. */
      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf4 v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        pre.intersect1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of the M triangles. */
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf4 v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene);
        return pre.occluded1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
    };

    /*! Intersects M motion blur quads with 1 ray */
    template<int M, bool filter>
    struct QuadMiMBIntersector1Moeller
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersector1MoellerTrumbore<M,filter> Precalculations;

      /*! Intersect a ray with the M quads and updates the hit. */
      static __forceinline void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time());
        pre.intersect(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of M quads. */
      static __forceinline bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time());
        return pre.occluded(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
      
      static __forceinline bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& quad)
      {
        return PrimitivePointQuery1<Primitive>::pointQuery(query, context, quad);
      }
    };

    /*! Intersects M motion blur quads with K rays. */
    template<int M, int K, bool filter>
    struct QuadMiMBIntersectorKMoeller
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersectorKMoellerTrumbore<M,K,filter> Precalculations;

      /*! Intersects K rays with M quads. */
      static __forceinline void intersect(const vbool<K>& valid_i, Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(normal.trav_prims,1,popcnt(valid_i),K);
          Vec3vf<K> v0,v1,v2,v3; quad.template gather<K>(valid_i,v0,v1,v2,v3,i,context->scene,ray.time());
          pre.intersectK(valid_i,ray,v0,v1,v2,v3,IntersectKEpilogM<M,K,filter>(ray,context,quad.geomID(),quad.primID(),i));
        }
      }

      /*! Test for K rays if they are occluded by any of the M quads. */
      static __forceinline vbool<K> occluded(const vbool<K>& valid_i, Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        vbool<K> valid0 = valid_i;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(shadow.trav_prims,1,popcnt(valid0),K);
          Vec3vf<K> v0,v1,v2,v3; quad.template gather<K>(valid_i,v0,v1,v2,v3,i,context->scene,ray.time());
          if (pre.intersectK(valid0,ray,v0,v1,v2,v3,OccludedKEpilogM<M,K,filter>(valid0,ray,context,quad.geomID(),quad.primID(),i)))
            break;
        }
        return !valid0;
      }
      
      /*! Intersect a ray with M quads and updates the hit. */
      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time()[k]);
        pre.intersect1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of the M quads. */
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time()[k]);
        return pre.occluded1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
    };

    /*! Intersects M motion blur quads with 1 ray */
    template<int M, bool filter>
    struct QuadMiMBIntersector1Pluecker
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersector1Pluecker<M,filter> Precalculations;

      /*! Intersect a ray with the M quads and updates the hit. */
      static __forceinline void intersect(const Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time());
        pre.intersect(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of M quads. */
      static __forceinline bool occluded(const Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time());
        return pre.occluded(ray,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
      
      static __forceinline bool pointQuery(PointQuery* query, PointQueryContext* context, const Primitive& quad)
      {
        return PrimitivePointQuery1<Primitive>::pointQuery(query, context, quad);
      }
    };

    /*! Intersects M motion blur quads with K rays. */
    template<int M, int K, bool filter>
    struct QuadMiMBIntersectorKPluecker
    {
      typedef QuadMi<M> Primitive;
      typedef QuadMIntersectorKPluecker<M,K,filter> Precalculations;

      /*! Intersects K rays with M quads. */
      static __forceinline void intersect(const vbool<K>& valid_i, Precalculations& pre, RayHitK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(normal.trav_prims,1,popcnt(valid_i),K);
          Vec3vf<K> v0,v1,v2,v3; quad.template gather<K>(valid_i,v0,v1,v2,v3,i,context->scene,ray.time());
          pre.intersectK(valid_i,ray,v0,v1,v2,v3,IntersectKEpilogM<M,K,filter>(ray,context,quad.geomID(),quad.primID(),i));
        }
      }

      /*! Test for K rays if they are occluded by any of the M quads. */
      static __forceinline vbool<K> occluded(const vbool<K>& valid_i, Precalculations& pre, RayK<K>& ray, RayQueryContext* context, const QuadMi<M>& quad)
      {
        vbool<K> valid0 = valid_i;
        for (size_t i=0; i<QuadMi<M>::max_size(); i++)
        {
          if (!quad.valid(i)) break;
          STAT3(shadow.trav_prims,1,popcnt(valid0),K);
          Vec3vf<K> v0,v1,v2,v3; quad.template gather<K>(valid_i,v0,v1,v2,v3,i,context->scene,ray.time());
          if (pre.intersectK(valid0,ray,v0,v1,v2,v3,OccludedKEpilogM<M,K,filter>(valid0,ray,context,quad.geomID(),quad.primID(),i)))
            break;
        }
        return !valid0;
      }
      
      /*! Intersect a ray with M quads and updates the hit. */
      static __forceinline void intersect(Precalculations& pre, RayHitK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(normal.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time()[k]);
        pre.intersect1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }

      /*! Test if the ray is occluded by one of the M quads. */
      static __forceinline bool occluded(Precalculations& pre, RayK<K>& ray, size_t k, RayQueryContext* context, const QuadMi<M>& quad)
      {
        STAT3(shadow.trav_prims,1,1,1);
        Vec3vf<M> v0,v1,v2,v3; quad.gather(v0,v1,v2,v3,context->scene,ray.time()[k]);
        return pre.occluded1(ray,k,context,v0,v1,v2,v3,quad.geomID(),quad.primID());
      }
    };
  }
}
