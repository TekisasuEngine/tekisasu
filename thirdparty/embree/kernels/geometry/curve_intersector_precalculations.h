/**************************************************************************/
/*  curve_intersector_precalculations.h                                   */
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
#include "../common/geometry.h"

namespace embree
{
  namespace isa
  {
    struct CurvePrecalculations1
    {
      float depth_scale;
      LinearSpace3fa ray_space;
           
      __forceinline CurvePrecalculations1() {}

      __forceinline CurvePrecalculations1(const Ray& ray, const void* ptr)
      {
        depth_scale = rsqrt(dot(ray.dir,ray.dir));
        LinearSpace3fa space = frame(depth_scale*ray.dir);
        space.vz *= depth_scale;
        ray_space = space.transposed();
      }
    };
    
    template<int K>
      struct CurvePrecalculationsK
    {
      vfloat<K> depth_scale;
      LinearSpace3fa ray_space[K];

      __forceinline CurvePrecalculationsK(const vbool<K>& valid, const RayK<K>& ray)
      {
        size_t mask = movemask(valid);
        depth_scale = rsqrt(dot(ray.dir,ray.dir));
        while (mask) {
          size_t k = bscf(mask);
          Vec3fa ray_dir_k = Vec3fa(ray.dir.x[k],ray.dir.y[k],ray.dir.z[k]);
          LinearSpace3fa ray_space_k = frame(depth_scale[k]*ray_dir_k);
          ray_space_k.vz *= depth_scale[k];
          ray_space[k] = ray_space_k.transposed();
        }
      }
    };
  }
}
