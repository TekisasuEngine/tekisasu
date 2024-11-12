/**************************************************************************/
/*  catmullclark_coefficients.h                                           */
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

#include "../common/geometry.h"

namespace embree
{
  static const size_t MAX_PATCH_VALENCE = 16;         //!< maximum number of vertices of a patch
  static const size_t MAX_RING_FACE_VALENCE = 64;     //!< maximum number of faces per ring
  static const size_t MAX_RING_EDGE_VALENCE = 2*64;   //!< maximum number of edges per ring

  class CatmullClarkPrecomputedCoefficients 
  {
  private:
    
    float table_cos_2PI_div_n[MAX_RING_FACE_VALENCE+1];

    float* table_limittangent_a[MAX_RING_FACE_VALENCE+1];
    float* table_limittangent_b[MAX_RING_FACE_VALENCE+1];
    float table_limittangent_c[MAX_RING_FACE_VALENCE+1];

    __forceinline float set_cos_2PI_div_n(const size_t n) { 
      if (unlikely(n == 0)) return 1.0f;
      return cosf(2.0f*float(pi)/(float)n); 
    }

    __forceinline float set_limittangent_a(const size_t i, const size_t n)  
    { 
      if (unlikely(n == 0)) return 1.0f;
      const float c0 = 1.0f/(float)n * 1.0f / sqrtf(4.0f + cosf(float(pi)/(float)n)*cosf(float(pi)/(float)n));
      const float c1 = (1.0f/(float)n + cosf(float(pi)/(float)n) * c0); 
      return cosf(2.0f*float(pi)*(float)i/(float)n) * c1;
    }

    __forceinline float set_limittangent_b(const size_t i, const size_t n)  
    { 
      if (unlikely(n == 0)) return 1.0f;
      const float c0 = 1.0f/(float)n * 1.0f / sqrtf(4.0f + cosf(float(pi)/(float)n)*cosf(float(pi)/(float)n));
      return cosf((2.0f*float(pi)*i+float(pi))/(float)n) * c0;
    }

    __forceinline float set_limittangent_c(const size_t n)  
    { 
      if (unlikely(n == 0)) return 1.0f;
      return 2.0f/16.0f * (5.0f + cosf(2.0f*float(pi)/(float)n) + cosf(float(pi)/(float)n) * sqrtf(18.0f+2.0f*cosf(2.0f*float(pi)/(float)n)));
    }

  public:

    __forceinline float cos_2PI_div_n(const size_t n)
    {
      if (likely(n <= MAX_RING_FACE_VALENCE))
        return table_cos_2PI_div_n[n];
      else
        return set_cos_2PI_div_n(n);
    }

    __forceinline float limittangent_a(const size_t i, const size_t n)
    {
      assert(n <= MAX_RING_FACE_VALENCE);
      assert(i < n);
      return table_limittangent_a[n][i];
    }

    __forceinline float limittangent_b(const size_t i, const size_t n)
    {
      assert(n <= MAX_RING_FACE_VALENCE);
      assert(i < n);
      return table_limittangent_b[n][i];
    }

    __forceinline float limittangent_c(const size_t n)
    {
      assert(n <= MAX_RING_FACE_VALENCE);
      return table_limittangent_c[n];
    }

    static CatmullClarkPrecomputedCoefficients table;
 
    CatmullClarkPrecomputedCoefficients();    
    ~CatmullClarkPrecomputedCoefficients();    
  };
}
