/**************************************************************************/
/*  sse.h                                                                 */
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

#include "../sys/platform.h"
#include "../sys/intrinsics.h"
#include "../sys/alloc.h"
#include "../math/constants.h"
#include "varying.h"

namespace embree 
{
#if defined(__aarch64__) || defined(__SSE4_1__)
  __forceinline __m128 blendv_ps(__m128 f, __m128 t, __m128 mask) { 
    return _mm_blendv_ps(f,t,mask);
  }
#else
  __forceinline __m128 blendv_ps(__m128 f, __m128 t, __m128 mask) { 
    return _mm_or_ps(_mm_and_ps(mask, t), _mm_andnot_ps(mask, f)); 
  }
#endif

  extern const __m128  mm_lookupmask_ps[16];
  extern const __m128d mm_lookupmask_pd[4];
}

#if defined(__AVX512VL__)
#include "vboolf4_avx512.h"
#else
#include "vboolf4_sse2.h"
#endif
#include "vint4_sse2.h"
#include "vuint4_sse2.h"
#include "vfloat4_sse2.h"
