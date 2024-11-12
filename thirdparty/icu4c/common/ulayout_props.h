/**************************************************************************/
/*  ulayout_props.h                                                       */
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

// © 2019 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// ulayout_props.h
// created: 2019feb12 Markus W. Scherer

#ifndef __ULAYOUT_PROPS_H__
#define __ULAYOUT_PROPS_H__

#include "unicode/utypes.h"

// file definitions ------------------------------------------------------------

#define ULAYOUT_DATA_NAME "ulayout"
#define ULAYOUT_DATA_TYPE "icu"

// data format "Layo"
#define ULAYOUT_FMT_0 0x4c
#define ULAYOUT_FMT_1 0x61
#define ULAYOUT_FMT_2 0x79
#define ULAYOUT_FMT_3 0x6f

// indexes into indexes[]
enum {
    // Element 0 stores the length of the indexes[] array.
    ULAYOUT_IX_INDEXES_LENGTH,
    // Elements 1..7 store the tops of consecutive code point tries.
    // No trie is stored if the difference between two of these is less than 16.
    ULAYOUT_IX_INPC_TRIE_TOP,
    ULAYOUT_IX_INSC_TRIE_TOP,
    ULAYOUT_IX_VO_TRIE_TOP,
    ULAYOUT_IX_RESERVED_TOP,

    ULAYOUT_IX_TRIES_TOP = 7,

    ULAYOUT_IX_MAX_VALUES = 9,

    // Length of indexes[]. Multiple of 4 to 16-align the tries.
    ULAYOUT_IX_COUNT = 12
};

constexpr int32_t ULAYOUT_MAX_INPC_SHIFT = 24;
constexpr int32_t ULAYOUT_MAX_INSC_SHIFT = 16;
constexpr int32_t ULAYOUT_MAX_VO_SHIFT = 8;

#endif  // __ULAYOUT_PROPS_H__
