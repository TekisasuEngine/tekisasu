/**************************************************************************/
/*  alphai_dec.h                                                          */
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
// Alpha decoder: internal header.
//
// Author: Urvang (urvang@google.com)

#ifndef WEBP_DEC_ALPHAI_DEC_H_
#define WEBP_DEC_ALPHAI_DEC_H_

#include "src/dec/webpi_dec.h"
#include "src/utils/filters_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VP8LDecoder;  // Defined in dec/vp8li.h.

typedef struct ALPHDecoder ALPHDecoder;
struct ALPHDecoder {
  int width_;
  int height_;
  int method_;
  WEBP_FILTER_TYPE filter_;
  int pre_processing_;
  struct VP8LDecoder* vp8l_dec_;
  VP8Io io_;
  int use_8b_decode_;  // Although alpha channel requires only 1 byte per
                       // pixel, sometimes VP8LDecoder may need to allocate
                       // 4 bytes per pixel internally during decode.
  uint8_t* output_;
  const uint8_t* prev_line_;   // last output row (or NULL)
};

//------------------------------------------------------------------------------
// internal functions. Not public.

// Deallocate memory associated to dec->alpha_plane_ decoding
void WebPDeallocateAlphaMemory(VP8Decoder* const dec);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}    // extern "C"
#endif

#endif  // WEBP_DEC_ALPHAI_DEC_H_
