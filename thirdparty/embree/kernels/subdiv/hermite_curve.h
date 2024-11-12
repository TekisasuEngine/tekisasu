/**************************************************************************/
/*  hermite_curve.h                                                       */
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

#include "../common/default.h"
#include "bezier_curve.h"

namespace embree
{
  template<typename Vertex>
    struct HermiteCurveT : BezierCurveT<Vertex>
    {
      __forceinline HermiteCurveT() {}

      __forceinline HermiteCurveT(const BezierCurveT<Vertex>& curve)
        : BezierCurveT<Vertex>(curve) {}
      
      __forceinline HermiteCurveT(const Vertex& v0, const Vertex& t0, const Vertex& v1, const Vertex& t1)
        : BezierCurveT<Vertex>(v0,madd(1.0f/3.0f,t0,v0),nmadd(1.0f/3.0f,t1,v1),v1) {}

      __forceinline HermiteCurveT<Vec3ff> xfm_pr(const LinearSpace3fa& space, const Vec3fa& p) const
      {
        const Vec3ff q0(xfmVector(space,this->v0-p), this->v0.w);
        const Vec3ff q1(xfmVector(space,this->v1-p), this->v1.w);
        const Vec3ff q2(xfmVector(space,this->v2-p), this->v2.w);
        const Vec3ff q3(xfmVector(space,this->v3-p), this->v3.w);
        return BezierCurveT<Vec3ff>(q0,q1,q2,q3);
      }
    };

  template<typename Vertex>
    __forceinline void convert(const HermiteCurveT<Vertex>& icurve, BezierCurveT<Vertex>& ocurve)
  {
    ocurve = BezierCurveT<Vertex>(icurve.v0,icurve.v1,icurve.v2,icurve.v3);
  }
  
  template<typename CurveGeometry>
  __forceinline HermiteCurveT<Vec3ff> enlargeRadiusToMinWidth(const RayQueryContext* context, const CurveGeometry* geom, const Vec3fa& ray_org, const HermiteCurveT<Vec3ff>& curve) {
    return HermiteCurveT<Vec3ff>(enlargeRadiusToMinWidth(context,geom,ray_org,BezierCurveT<Vec3ff>(curve)));
  }
  
  typedef HermiteCurveT<Vec3fa> HermiteCurve3fa;
}

