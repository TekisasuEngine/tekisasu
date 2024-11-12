/**************************************************************************/
/*  grid_soa_intersector1.h                                               */
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

#include "grid_soa.h"
#include "../common/ray.h"
#include "triangle_intersector_pluecker.h"

namespace embree
{
  namespace isa
  {
    class GridSOAIntersector1
    {
    public:
      typedef void Primitive;
      
      class Precalculations
      { 
      public:
        __forceinline Precalculations (const Ray& ray, const void* ptr)
          : grid(nullptr) {}
        
      public:
        GridSOA* grid;
        int itime;
        float ftime;
      };
      
      template<typename Loader>
        static __forceinline void intersect(RayHit& ray,
                                            RayQueryContext* context, 
                                            const float* const grid_x,
                                            const size_t line_offset,
                                            const size_t lines,
                                            Precalculations& pre)
      {
        typedef typename Loader::vfloat vfloat;
        const size_t dim_offset    = pre.grid->dim_offset;
        const float* const grid_y  = grid_x + 1 * dim_offset;
        const float* const grid_z  = grid_x + 2 * dim_offset;
        const float* const grid_uv = grid_x + 3 * dim_offset;
        Vec3<vfloat> v0, v1, v2;
        Loader::gather(grid_x,grid_y,grid_z,line_offset,lines,v0,v1,v2);       
        GridSOA::MapUV<Loader> mapUV(grid_uv,line_offset,lines);
        PlueckerIntersector1<Loader::M> intersector(ray,nullptr);
        intersector.intersect(ray,v0,v1,v2,mapUV,Intersect1EpilogMU<Loader::M,true>(ray,context,pre.grid->geomID(),pre.grid->primID()));
      };
      
      template<typename Loader>
        static __forceinline bool occluded(Ray& ray,
                                           RayQueryContext* context, 
                                           const float* const grid_x,
                                           const size_t line_offset,
                                           const size_t lines,
                                           Precalculations& pre)
      {
        typedef typename Loader::vfloat vfloat;
        const size_t dim_offset    = pre.grid->dim_offset;
        const float* const grid_y  = grid_x + 1 * dim_offset;
        const float* const grid_z  = grid_x + 2 * dim_offset;
        const float* const grid_uv = grid_x + 3 * dim_offset;

        Vec3<vfloat> v0, v1, v2;
        Loader::gather(grid_x,grid_y,grid_z,line_offset,lines,v0,v1,v2);
        
        GridSOA::MapUV<Loader> mapUV(grid_uv,line_offset,lines);
        PlueckerIntersector1<Loader::M> intersector(ray,nullptr);
        return intersector.intersect(ray,v0,v1,v2,mapUV,Occluded1EpilogMU<Loader::M,true>(ray,context,pre.grid->geomID(),pre.grid->primID()));
      }
      
      /*! Intersect a ray with the primitive. */
      static __forceinline void intersect(Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive* prim, size_t& lazy_node) 
      {
        const size_t line_offset   = pre.grid->width;
        const size_t lines         = pre.grid->height;
        const float* const grid_x  = pre.grid->decodeLeaf(0,prim);
        
#if defined(__AVX__)
        intersect<GridSOA::Gather3x3>( ray, context, grid_x, line_offset, lines, pre);
#else
        intersect<GridSOA::Gather2x3>(ray, context, grid_x            , line_offset, lines, pre);
        if (likely(lines > 2))
          intersect<GridSOA::Gather2x3>(ray, context, grid_x+line_offset, line_offset, lines, pre);
#endif
      }
      
      /*! Test if the ray is occluded by the primitive */
      static __forceinline bool occluded(Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive* prim, size_t& lazy_node)
      {
        const size_t line_offset   = pre.grid->width;
        const size_t lines         = pre.grid->height;
        const float* const grid_x  = pre.grid->decodeLeaf(0,prim);
        
#if defined(__AVX__)
        return occluded<GridSOA::Gather3x3>( ray, context, grid_x, line_offset, lines, pre);
#else
        if (occluded<GridSOA::Gather2x3>(ray, context, grid_x            , line_offset, lines, pre)) return true;
        if (likely(lines > 2))
          if (occluded<GridSOA::Gather2x3>(ray, context, grid_x+line_offset, line_offset, lines, pre)) return true;
#endif
        return false;
      }      
    };

    class GridSOAMBIntersector1
    {
    public:
      typedef void Primitive;
      typedef GridSOAIntersector1::Precalculations Precalculations;
      
      template<typename Loader>
        static __forceinline void intersect(RayHit& ray, const float ftime,
                                            RayQueryContext* context, 
                                            const float* const grid_x,
                                            const size_t line_offset,
                                            const size_t lines,
                                            Precalculations& pre)
      {
        typedef typename Loader::vfloat vfloat;
        const size_t dim_offset    = pre.grid->dim_offset;
        const size_t grid_offset   = pre.grid->gridBytes >> 2;
        const float* const grid_y  = grid_x + 1 * dim_offset;
        const float* const grid_z  = grid_x + 2 * dim_offset;
        const float* const grid_uv = grid_x + 3 * dim_offset;

        Vec3<vfloat> a0, a1, a2;
        Loader::gather(grid_x,grid_y,grid_z,line_offset,lines,a0,a1,a2);

        Vec3<vfloat> b0, b1, b2;
        Loader::gather(grid_x+grid_offset,grid_y+grid_offset,grid_z+grid_offset,line_offset,lines,b0,b1,b2);

        Vec3<vfloat> v0 = lerp(a0,b0,vfloat(ftime));
        Vec3<vfloat> v1 = lerp(a1,b1,vfloat(ftime));
        Vec3<vfloat> v2 = lerp(a2,b2,vfloat(ftime));

        GridSOA::MapUV<Loader> mapUV(grid_uv,line_offset,lines);
        PlueckerIntersector1<Loader::M> intersector(ray,nullptr);
        intersector.intersect(ray,v0,v1,v2,mapUV,Intersect1EpilogMU<Loader::M,true>(ray,context,pre.grid->geomID(),pre.grid->primID()));
      };
      
      template<typename Loader>
        static __forceinline bool occluded(Ray& ray, const float ftime,
                                           RayQueryContext* context, 
                                           const float* const grid_x,
                                           const size_t line_offset,
                                           const size_t lines,
                                           Precalculations& pre)
      {
        typedef typename Loader::vfloat vfloat;
        const size_t dim_offset    = pre.grid->dim_offset;
        const size_t grid_offset   = pre.grid->gridBytes >> 2;
        const float* const grid_y  = grid_x + 1 * dim_offset;
        const float* const grid_z  = grid_x + 2 * dim_offset;
        const float* const grid_uv = grid_x + 3 * dim_offset;

        Vec3<vfloat> a0, a1, a2;
        Loader::gather(grid_x,grid_y,grid_z,line_offset,lines,a0,a1,a2);

        Vec3<vfloat> b0, b1, b2;
        Loader::gather(grid_x+grid_offset,grid_y+grid_offset,grid_z+grid_offset,line_offset,lines,b0,b1,b2);
       
        Vec3<vfloat> v0 = lerp(a0,b0,vfloat(ftime));
        Vec3<vfloat> v1 = lerp(a1,b1,vfloat(ftime));
        Vec3<vfloat> v2 = lerp(a2,b2,vfloat(ftime));
        
        GridSOA::MapUV<Loader> mapUV(grid_uv,line_offset,lines);
        PlueckerIntersector1<Loader::M> intersector(ray,nullptr);
        return intersector.intersect(ray,v0,v1,v2,mapUV,Occluded1EpilogMU<Loader::M,true>(ray,context,pre.grid->geomID(),pre.grid->primID()));
      }
      
      /*! Intersect a ray with the primitive. */
      static __forceinline void intersect(Precalculations& pre, RayHit& ray, RayQueryContext* context, const Primitive* prim, size_t& lazy_node) 
      { 
        const size_t line_offset   = pre.grid->width;
        const size_t lines         = pre.grid->height;
        const float* const grid_x  = pre.grid->decodeLeaf(pre.itime,prim);
        
#if defined(__AVX__)
        intersect<GridSOA::Gather3x3>( ray, pre.ftime, context, grid_x, line_offset, lines, pre);
#else
        intersect<GridSOA::Gather2x3>(ray, pre.ftime, context, grid_x, line_offset, lines, pre);
        if (likely(lines > 2))
          intersect<GridSOA::Gather2x3>(ray, pre.ftime, context, grid_x+line_offset, line_offset, lines, pre);
#endif
      }
      
      /*! Test if the ray is occluded by the primitive */
      static __forceinline bool occluded(Precalculations& pre, Ray& ray, RayQueryContext* context, const Primitive* prim, size_t& lazy_node)
      {
        const size_t line_offset   = pre.grid->width;
        const size_t lines         = pre.grid->height;
        const float* const grid_x  = pre.grid->decodeLeaf(pre.itime,prim);
        
#if defined(__AVX__)
        return occluded<GridSOA::Gather3x3>( ray, pre.ftime, context, grid_x, line_offset, lines, pre);
#else
        if (occluded<GridSOA::Gather2x3>(ray, pre.ftime, context, grid_x            , line_offset, lines, pre)) return true;
        if (likely(lines > 2))
          if (occluded<GridSOA::Gather2x3>(ray, pre.ftime, context, grid_x+line_offset, line_offset, lines, pre)) return true;
#endif
        return false;
      }      
    };
  }
}
