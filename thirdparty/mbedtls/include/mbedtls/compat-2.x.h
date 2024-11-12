/**************************************************************************/
/*  compat-2.x.h                                                          */
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

/**
 * \file compat-2.x.h
 *
 * \brief Compatibility definitions
 *
 * \deprecated Use the new names directly instead
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#if defined(MBEDTLS_DEPRECATED_WARNING)
#warning "Including compat-2.x.h is deprecated"
#endif

#ifndef MBEDTLS_COMPAT2X_H
#define MBEDTLS_COMPAT2X_H

/*
 * Macros for renamed functions
 */
#define mbedtls_ctr_drbg_update_ret   mbedtls_ctr_drbg_update
#define mbedtls_hmac_drbg_update_ret  mbedtls_hmac_drbg_update
#define mbedtls_md5_starts_ret        mbedtls_md5_starts
#define mbedtls_md5_update_ret        mbedtls_md5_update
#define mbedtls_md5_finish_ret        mbedtls_md5_finish
#define mbedtls_md5_ret               mbedtls_md5
#define mbedtls_ripemd160_starts_ret  mbedtls_ripemd160_starts
#define mbedtls_ripemd160_update_ret  mbedtls_ripemd160_update
#define mbedtls_ripemd160_finish_ret  mbedtls_ripemd160_finish
#define mbedtls_ripemd160_ret         mbedtls_ripemd160
#define mbedtls_sha1_starts_ret       mbedtls_sha1_starts
#define mbedtls_sha1_update_ret       mbedtls_sha1_update
#define mbedtls_sha1_finish_ret       mbedtls_sha1_finish
#define mbedtls_sha1_ret              mbedtls_sha1
#define mbedtls_sha256_starts_ret     mbedtls_sha256_starts
#define mbedtls_sha256_update_ret     mbedtls_sha256_update
#define mbedtls_sha256_finish_ret     mbedtls_sha256_finish
#define mbedtls_sha256_ret            mbedtls_sha256
#define mbedtls_sha512_starts_ret     mbedtls_sha512_starts
#define mbedtls_sha512_update_ret     mbedtls_sha512_update
#define mbedtls_sha512_finish_ret     mbedtls_sha512_finish
#define mbedtls_sha512_ret            mbedtls_sha512

#endif /* MBEDTLS_COMPAT2X_H */
