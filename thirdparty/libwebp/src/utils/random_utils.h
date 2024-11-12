/**************************************************************************/
/*  random_utils.h                                                        */
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

// Copyright 2013 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
// Pseudo-random utilities
//
// Author: Skal (pascal.massimino@gmail.com)

#ifndef WEBP_UTILS_RANDOM_UTILS_H_
#define WEBP_UTILS_RANDOM_UTILS_H_

#include <assert.h>
#include "src/webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VP8_RANDOM_DITHER_FIX 8   // fixed-point precision for dithering
#define VP8_RANDOM_TABLE_SIZE 55

typedef struct {
  int index1_, index2_;
  uint32_t tab_[VP8_RANDOM_TABLE_SIZE];
  int amp_;
} VP8Random;

// Initializes random generator with an amplitude 'dithering' in range [0..1].
void VP8InitRandom(VP8Random* const rg, float dithering);

// Returns a centered pseudo-random number with 'num_bits' amplitude.
// (uses D.Knuth's Difference-based random generator).
// 'amp' is in VP8_RANDOM_DITHER_FIX fixed-point precision.
static WEBP_INLINE int VP8RandomBits2(VP8Random* const rg, int num_bits,
                                      int amp) {
  int diff;
  assert(num_bits + VP8_RANDOM_DITHER_FIX <= 31);
  diff = rg->tab_[rg->index1_] - rg->tab_[rg->index2_];
  if (diff < 0) diff += (1u << 31);
  rg->tab_[rg->index1_] = diff;
  if (++rg->index1_ == VP8_RANDOM_TABLE_SIZE) rg->index1_ = 0;
  if (++rg->index2_ == VP8_RANDOM_TABLE_SIZE) rg->index2_ = 0;
  // sign-extend, 0-center
  diff = (int)((uint32_t)diff << 1) >> (32 - num_bits);
  diff = (diff * amp) >> VP8_RANDOM_DITHER_FIX;  // restrict range
  diff += 1 << (num_bits - 1);                   // shift back to 0.5-center
  return diff;
}

static WEBP_INLINE int VP8RandomBits(VP8Random* const rg, int num_bits) {
  return VP8RandomBits2(rg, num_bits, rg->amp_);
}

#ifdef __cplusplus
}    // extern "C"
#endif

#endif  // WEBP_UTILS_RANDOM_UTILS_H_
