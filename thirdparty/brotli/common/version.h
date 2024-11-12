/**************************************************************************/
/*  version.h                                                             */
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

/* Copyright 2016 Google Inc. All Rights Reserved.

   Distributed under MIT license.
   See file LICENSE for detail or copy at https://opensource.org/licenses/MIT
*/

/* Version definition. */

#ifndef BROTLI_COMMON_VERSION_H_
#define BROTLI_COMMON_VERSION_H_

/* Compose 3 components into a single number. In a hexadecimal representation
   B and C components occupy exactly 3 digits. */
#define BROTLI_MAKE_HEX_VERSION(A, B, C) ((A << 24) | (B << 12) | C)

/* Those macros should only be used when library is compiled together with
   the client. If library is dynamically linked, use BrotliDecoderVersion and
   BrotliEncoderVersion methods. */

#define BROTLI_VERSION_MAJOR 1
#define BROTLI_VERSION_MINOR 1
#define BROTLI_VERSION_PATCH 0

#define BROTLI_VERSION BROTLI_MAKE_HEX_VERSION(                     \
  BROTLI_VERSION_MAJOR, BROTLI_VERSION_MINOR, BROTLI_VERSION_PATCH)

/* This macro is used by build system to produce Libtool-friendly soname. See
   https://www.gnu.org/software/libtool/manual/html_node/Libtool-versioning.html
   Version evolution rules:
    - interfaces added (or change is compatible)      -> current+1:0:age+1
    - interfaces removed (or changed is incompatible) -> current+1:0:0
    - interfaces not changed                          -> current:revision+1:age
 */

#define BROTLI_ABI_CURRENT  2
#define BROTLI_ABI_REVISION 0
#define BROTLI_ABI_AGE      1

#if BROTLI_VERSION_MAJOR != (BROTLI_ABI_CURRENT - BROTLI_ABI_AGE)
#error ABI/API version inconsistency
#endif

#if BROTLI_VERSION_MINOR != BROTLI_ABI_AGE
#error ABI/API version inconsistency
#endif

#if BROTLI_VERSION_PATCH != BROTLI_ABI_REVISION
#error ABI/API version inconsistency
#endif

#endif  /* BROTLI_COMMON_VERSION_H_ */
