/**************************************************************************/
/*  animi.h                                                               */
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

// Copyright 2016 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
// Internal header for animation related functions.
//
// Author: Hui Su (huisu@google.com)

#ifndef WEBP_MUX_ANIMI_H_
#define WEBP_MUX_ANIMI_H_

#include "src/webp/mux.h"

#ifdef __cplusplus
extern "C" {
#endif

// Picks the optimal rectangle between two pictures, starting with initial
// values of offsets and dimensions that are passed in. The initial
// values will be clipped, if necessary, to make sure the rectangle is
// within the canvas. "use_argb" must be true for both pictures.
// Parameters:
//   prev_canvas, curr_canvas - (in) two input pictures to compare.
//   is_lossless, quality - (in) encoding settings.
//   x_offset, y_offset, width, height - (in/out) rectangle between the two
//                                                input pictures.
// Returns true on success.
int WebPAnimEncoderRefineRect(
    const struct WebPPicture* const prev_canvas,
    const struct WebPPicture* const curr_canvas,
    int is_lossless, float quality, int* const x_offset, int* const y_offset,
    int* const width, int* const height);

#ifdef __cplusplus
}    // extern "C"
#endif

#endif  // WEBP_MUX_ANIMI_H_
