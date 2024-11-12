/**************************************************************************/
/*  formatsize.h                                                          */
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

/* -*- tab-width: 4; -*- */
/* vi: set sw=2 ts=4 expandtab: */

/*
 * Copyright 2019-2020 The Khronos Group Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @internal
 * @file
 * @~English
 *
 * @brief Struct for returning size information about an image format.
 *
 * @author Mark Callow, www.edgewise-consulting.com
 */

#ifndef _FORMATSIZE_H_
#define _FORMATSIZE_H_

#include "ktx.h"

typedef enum ktxFormatSizeFlagBits {
    KTX_FORMAT_SIZE_PACKED_BIT                = 0x00000001,
    KTX_FORMAT_SIZE_COMPRESSED_BIT            = 0x00000002,
    KTX_FORMAT_SIZE_PALETTIZED_BIT            = 0x00000004,
    KTX_FORMAT_SIZE_DEPTH_BIT                 = 0x00000008,
    KTX_FORMAT_SIZE_STENCIL_BIT               = 0x00000010,
    KTX_FORMAT_SIZE_YUVSDA_BIT                = 0x00000020,
} ktxFormatSizeFlagBits;

typedef ktx_uint32_t ktxFormatSizeFlags;

/**
 * @brief Structure for holding size information for a texture format.
 */
typedef struct ktxFormatSize {
    ktxFormatSizeFlags  flags;
    unsigned int        paletteSizeInBits;  // For KTX1.
    unsigned int        blockSizeInBits;
    unsigned int        blockWidth;         // in texels
    unsigned int        blockHeight;        // in texels
    unsigned int        blockDepth;         // in texels
    unsigned int        minBlocksX;         // Minimum required number of blocks
    unsigned int        minBlocksY;
} ktxFormatSize;

#ifdef __cplusplus
extern "C" {
#endif

bool ktxFormatSize_initFromDfd(ktxFormatSize* This, ktx_uint32_t* pDfd);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _FORMATSIZE_H_ */
