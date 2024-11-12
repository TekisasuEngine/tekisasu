/**************************************************************************/
/*  zstd_decompress_block.h                                               */
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

/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
 */


#ifndef ZSTD_DEC_BLOCK_H
#define ZSTD_DEC_BLOCK_H

/*-*******************************************************
 *  Dependencies
 *********************************************************/
#include "../common/zstd_deps.h"   /* size_t */
#include "../zstd.h"    /* DCtx, and some public functions */
#include "../common/zstd_internal.h"  /* blockProperties_t, and some public functions */
#include "zstd_decompress_internal.h"  /* ZSTD_seqSymbol */


/* ===   Prototypes   === */

/* note: prototypes already published within `zstd.h` :
 * ZSTD_decompressBlock()
 */

/* note: prototypes already published within `zstd_internal.h` :
 * ZSTD_getcBlockSize()
 * ZSTD_decodeSeqHeaders()
 */


 /* Streaming state is used to inform allocation of the literal buffer */
typedef enum {
    not_streaming = 0,
    is_streaming = 1
} streaming_operation;

/* ZSTD_decompressBlock_internal() :
 * decompress block, starting at `src`,
 * into destination buffer `dst`.
 * @return : decompressed block size,
 *           or an error code (which can be tested using ZSTD_isError())
 */
size_t ZSTD_decompressBlock_internal(ZSTD_DCtx* dctx,
                               void* dst, size_t dstCapacity,
                         const void* src, size_t srcSize, const streaming_operation streaming);

/* ZSTD_buildFSETable() :
 * generate FSE decoding table for one symbol (ll, ml or off)
 * this function must be called with valid parameters only
 * (dt is large enough, normalizedCounter distribution total is a power of 2, max is within range, etc.)
 * in which case it cannot fail.
 * The workspace must be 4-byte aligned and at least ZSTD_BUILD_FSE_TABLE_WKSP_SIZE bytes, which is
 * defined in zstd_decompress_internal.h.
 * Internal use only.
 */
void ZSTD_buildFSETable(ZSTD_seqSymbol* dt,
             const short* normalizedCounter, unsigned maxSymbolValue,
             const U32* baseValue, const U8* nbAdditionalBits,
                   unsigned tableLog, void* wksp, size_t wkspSize,
                   int bmi2);

/* Internal definition of ZSTD_decompressBlock() to avoid deprecation warnings. */
size_t ZSTD_decompressBlock_deprecated(ZSTD_DCtx* dctx,
                            void* dst, size_t dstCapacity,
                      const void* src, size_t srcSize);


#endif /* ZSTD_DEC_BLOCK_H */
