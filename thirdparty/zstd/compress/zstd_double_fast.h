/**************************************************************************/
/*  zstd_double_fast.h                                                    */
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

#ifndef ZSTD_DOUBLE_FAST_H
#define ZSTD_DOUBLE_FAST_H

#if defined (__cplusplus)
extern "C" {
#endif

#include "../common/mem.h"      /* U32 */
#include "zstd_compress_internal.h"     /* ZSTD_CCtx, size_t */

#ifndef ZSTD_EXCLUDE_DFAST_BLOCK_COMPRESSOR

void ZSTD_fillDoubleHashTable(ZSTD_matchState_t* ms,
                              void const* end, ZSTD_dictTableLoadMethod_e dtlm,
                              ZSTD_tableFillPurpose_e tfp);

size_t ZSTD_compressBlock_doubleFast(
        ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        void const* src, size_t srcSize);
size_t ZSTD_compressBlock_doubleFast_dictMatchState(
        ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        void const* src, size_t srcSize);
size_t ZSTD_compressBlock_doubleFast_extDict(
        ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        void const* src, size_t srcSize);

#define ZSTD_COMPRESSBLOCK_DOUBLEFAST ZSTD_compressBlock_doubleFast
#define ZSTD_COMPRESSBLOCK_DOUBLEFAST_DICTMATCHSTATE ZSTD_compressBlock_doubleFast_dictMatchState
#define ZSTD_COMPRESSBLOCK_DOUBLEFAST_EXTDICT ZSTD_compressBlock_doubleFast_extDict
#else
#define ZSTD_COMPRESSBLOCK_DOUBLEFAST NULL
#define ZSTD_COMPRESSBLOCK_DOUBLEFAST_DICTMATCHSTATE NULL
#define ZSTD_COMPRESSBLOCK_DOUBLEFAST_EXTDICT NULL
#endif /* ZSTD_EXCLUDE_DFAST_BLOCK_COMPRESSOR */

#if defined (__cplusplus)
}
#endif

#endif /* ZSTD_DOUBLE_FAST_H */
