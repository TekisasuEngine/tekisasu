/**************************************************************************/
/*  palette.h                                                             */
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

// Copyright 2023 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
// Utilities for palette analysis.
//
// Author: Vincent Rabaud (vrabaud@google.com)

#ifndef WEBP_UTILS_PALETTE_H_
#define WEBP_UTILS_PALETTE_H_

#include "src/webp/types.h"

struct WebPPicture;

// The different ways a palette can be sorted.
typedef enum PaletteSorting {
  kSortedDefault = 0,
  // Sorts by minimizing L1 deltas between consecutive colors, giving more
  // weight to RGB colors.
  kMinimizeDelta = 1,
  // Implements the modified Zeng method from "A Survey on Palette Reordering
  // Methods for Improving the Compression of Color-Indexed Images" by Armando
  // J. Pinho and Antonio J. R. Neves.
  kModifiedZeng = 2,
  kUnusedPalette = 3,
  kPaletteSortingNum = 4
} PaletteSorting;

// Returns the index of 'color' in the sorted palette 'sorted' of size
// 'num_colors'.
int SearchColorNoIdx(const uint32_t sorted[], uint32_t color, int num_colors);

// Sort palette in increasing order and prepare an inverse mapping array.
void PrepareMapToPalette(const uint32_t palette[], uint32_t num_colors,
                         uint32_t sorted[], uint32_t idx_map[]);

// Returns count of unique colors in 'pic', assuming pic->use_argb is true.
// If the unique color count is more than MAX_PALETTE_SIZE, returns
// MAX_PALETTE_SIZE+1.
// If 'palette' is not NULL and the number of unique colors is less than or
// equal to MAX_PALETTE_SIZE, also outputs the actual unique colors into
// 'palette' in a sorted order. Note: 'palette' is assumed to be an array
// already allocated with at least MAX_PALETTE_SIZE elements.
int GetColorPalette(const struct WebPPicture* const pic,
                    uint32_t* const palette);

// Sorts the palette according to the criterion defined by 'method'.
// 'palette_sorted' is the input palette sorted lexicographically, as done in
// PrepareMapToPalette. Returns 0 on memory allocation error.
int PaletteSort(PaletteSorting method, const struct WebPPicture* const pic,
                const uint32_t* const palette_sorted, uint32_t num_colors,
                uint32_t* const palette);

#endif  // WEBP_UTILS_PALETTE_H_
