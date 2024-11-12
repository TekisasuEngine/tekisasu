/**************************************************************************/
/*  line_intersector.h                                                    */
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
#include "curve_intersector_precalculations.h"

namespace embree
{
  namespace isa
  {
    template<int M>
      struct LineIntersectorHitM
      {
        __forceinline LineIntersectorHitM() {}

        __forceinline LineIntersectorHitM(const vfloat<M>& u, const vfloat<M>& v, const vfloat<M>& t, const Vec3vf<M>& Ng)
          : vu(u), vv(v), vt(t), vNg(Ng) {}
        
        __forceinline void finalize() {}
        
        __forceinline Vec2f uv (const size_t i) const { return Vec2f(vu[i],vv[i]); }
        __forceinline float t  (const size_t i) const { return vt[i]; }
        __forceinline Vec3fa Ng(const size_t i) const { return Vec3fa(vNg.x[i],vNg.y[i],vNg.z[i]); }

        __forceinline Vec2vf<M> uv() const { return Vec2vf<M>(vu,vv); }
        __forceinline vfloat<M> t () const { return vt; }
        __forceinline Vec3vf<M> Ng() const { return vNg; }
        
      public:
        vfloat<M> vu;
        vfloat<M> vv;
        vfloat<M> vt;
        Vec3vf<M> vNg;
      };
    
    template<int M>
      struct FlatLinearCurveIntersector1
      {
        typedef CurvePrecalculations1 Precalculations;
        
        template<typename Ray, typename Epilog>
        static __forceinline bool intersect(const vbool<M>& valid_i,
                                            Ray& ray,
                                            RayQueryContext* context,
                                            const LineSegments* geom,
                                            const Precalculations& pre,
                                            const Vec4vf<M>& v0i, const Vec4vf<M>& v1i,
                                            const Epilog& epilog)
        {
          /* transform end points into ray space */
          vbool<M> valid = valid_i;
          vfloat<M> depth_scale = pre.depth_scale;
          LinearSpace3<Vec3vf<M>> ray_space = pre.ray_space;

          const Vec3vf<M> ray_org ((Vec3fa)ray.org);
          const Vec4vf<M> v0 = enlargeRadiusToMinWidth<M>(context,geom,ray_org,v0i);
          const Vec4vf<M> v1 = enlargeRadiusToMinWidth<M>(context,geom,ray_org,v1i);
          
          Vec4vf<M> p0(xfmVector(ray_space,v0.xyz()-ray_org), v0.w);
          Vec4vf<M> p1(xfmVector(ray_space,v1.xyz()-ray_org), v1.w);
          
          /* approximative intersection with cone */
          const Vec4vf<M> v = p1-p0;
          const Vec4vf<M> w = -p0;
          const vfloat<M> d0 = madd(w.x,v.x,w.y*v.y);
          const vfloat<M> d1 = madd(v.x,v.x,v.y*v.y);
          const vfloat<M> u = clamp(d0*rcp(d1),vfloat<M>(zero),vfloat<M>(one));
          const Vec4vf<M> p = madd(u,v,p0);
          const vfloat<M> t = p.z;
          const vfloat<M> d2 = madd(p.x,p.x,p.y*p.y);
          const vfloat<M> r = p.w;
          const vfloat<M> r2 = r*r;
          valid &= (d2 <= r2) & (vfloat<M>(ray.tnear()) <= t) & (t <= vfloat<M>(ray.tfar));
          if (EMBREE_CURVE_SELF_INTERSECTION_AVOIDANCE_FACTOR != 0.0f) 
            valid &= t > float(EMBREE_CURVE_SELF_INTERSECTION_AVOIDANCE_FACTOR)*r*depth_scale; // ignore self intersections
          if (unlikely(none(valid))) return false;
          
          /* ignore denormalized segments */
          const Vec3vf<M> T = v1.xyz()-v0.xyz();
          valid &= (T.x != vfloat<M>(zero)) | (T.y != vfloat<M>(zero)) | (T.z != vfloat<M>(zero));
          if (unlikely(none(valid))) return false;
          
          /* update hit information */
          LineIntersectorHitM<M> hit(u,zero,t,T);
          return epilog(valid,hit);
        }
      };
    
    template<int M, int K>
      struct FlatLinearCurveIntersectorK
      {
        typedef CurvePrecalculationsK<K> Precalculations;
        
        template<typename Epilog>
        static __forceinline bool intersect(const vbool<M>& valid_i,
                                            RayK<K>& ray, size_t k,
                                            RayQueryContext* context,
                                            const LineSegments* geom,
                                            const Precalculations& pre,
                                            const Vec4vf<M>& v0i, const Vec4vf<M>& v1i,
                                            const Epilog& epilog)
        {
          /* transform end points into ray space */
          vbool<M> valid = valid_i;
          vfloat<M> depth_scale = pre.depth_scale[k];
          LinearSpace3<Vec3vf<M>> ray_space = pre.ray_space[k];
          const Vec3vf<M> ray_org(ray.org.x[k],ray.org.y[k],ray.org.z[k]);
          const Vec3vf<M> ray_dir(ray.dir.x[k],ray.dir.y[k],ray.dir.z[k]);

          const Vec4vf<M> v0 = enlargeRadiusToMinWidth<M>(context,geom,ray_org,v0i);
          const Vec4vf<M> v1 = enlargeRadiusToMinWidth<M>(context,geom,ray_org,v1i);
          
          Vec4vf<M> p0(xfmVector(ray_space,v0.xyz()-ray_org), v0.w);
          Vec4vf<M> p1(xfmVector(ray_space,v1.xyz()-ray_org), v1.w);
          
          /* approximative intersection with cone */
          const Vec4vf<M> v = p1-p0;
          const Vec4vf<M> w = -p0;
          const vfloat<M> d0 = madd(w.x,v.x,w.y*v.y);
          const vfloat<M> d1 = madd(v.x,v.x,v.y*v.y);
          const vfloat<M> u = clamp(d0*rcp(d1),vfloat<M>(zero),vfloat<M>(one));
          const Vec4vf<M> p = madd(u,v,p0);
          const vfloat<M> t = p.z;
          const vfloat<M> d2 = madd(p.x,p.x,p.y*p.y);
          const vfloat<M> r = p.w;
          const vfloat<M> r2 = r*r;
          valid &= (d2 <= r2) & (vfloat<M>(ray.tnear()[k]) <= t) & (t <= vfloat<M>(ray.tfar[k]));
          if (EMBREE_CURVE_SELF_INTERSECTION_AVOIDANCE_FACTOR != 0.0f) 
            valid &= t > float(EMBREE_CURVE_SELF_INTERSECTION_AVOIDANCE_FACTOR)*r*depth_scale; // ignore self intersections
          if (unlikely(none(valid))) return false;
          
          /* ignore denormalized segments */
          const Vec3vf<M> T = v1.xyz()-v0.xyz();
          valid &= (T.x != vfloat<M>(zero)) | (T.y != vfloat<M>(zero)) | (T.z != vfloat<M>(zero));
          if (unlikely(none(valid))) return false;
          
          /* update hit information */
          LineIntersectorHitM<M> hit(u,zero,t,T);
          return epilog(valid,hit);
        }
      };
  }
}
