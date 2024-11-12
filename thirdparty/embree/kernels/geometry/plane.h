/**************************************************************************/
/*  plane.h                                                               */
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

namespace embree
{
  namespace isa
  {
    struct HalfPlane
    {
      const Vec3fa P;  //!< plane origin
      const Vec3fa N;  //!< plane normal

      __forceinline HalfPlane(const Vec3fa& P, const Vec3fa& N) 
        : P(P), N(N) {}
      
      __forceinline BBox1f intersect(const Vec3fa& ray_org, const Vec3fa& ray_dir) const
      {
        Vec3fa O = Vec3fa(ray_org) - P;
        Vec3fa D = Vec3fa(ray_dir);
        float ON = dot(O,N);
        float DN = dot(D,N);
        bool eps = abs(DN) < min_rcp_input;
        float t = -ON*rcp(DN);
        float lower = select(eps || DN < 0.0f, float(neg_inf), t);
        float upper = select(eps || DN > 0.0f, float(pos_inf), t);
        return BBox1f(lower,upper);
      }
    };

    template<int M>
      struct HalfPlaneN
      {
        const Vec3vf<M> P;  //!< plane origin
        const Vec3vf<M> N;  //!< plane normal

        __forceinline HalfPlaneN(const Vec3vf<M>& P, const Vec3vf<M>& N)
          : P(P), N(N) {}

        __forceinline BBox<vfloat<M>> intersect(const Vec3fa& ray_org, const Vec3fa& ray_dir) const
        {
          Vec3vf<M> O = Vec3vf<M>((Vec3fa)ray_org) - P;
          Vec3vf<M> D = Vec3vf<M>((Vec3fa)ray_dir);
          vfloat<M> ON = dot(O,N);
          vfloat<M> DN = dot(D,N);
          vbool<M> eps = abs(DN) < min_rcp_input;
          vfloat<M> t = -ON*rcp(DN);
          vfloat<M> lower = select(eps | DN < 0.0f, vfloat<M>(neg_inf), t);
          vfloat<M> upper = select(eps | DN > 0.0f, vfloat<M>(pos_inf), t);
          return BBox<vfloat<M>>(lower,upper);
        }
      };
  }
}
