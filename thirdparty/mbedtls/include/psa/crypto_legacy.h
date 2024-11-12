/**************************************************************************/
/*  crypto_legacy.h                                                       */
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
 * \file psa/crypto_legacy.h
 *
 * \brief Add temporary suppport for deprecated symbols before they are
 *        removed from the library.
 *
 * PSA_WANT_KEY_TYPE_xxx_KEY_PAIR and MBEDTLS_PSA_ACCEL_KEY_TYPE_xxx_KEY_PAIR
 * symbols are deprecated.
 * New symols add a suffix to that base name in order to clearly state what is
 * the expected use for the key (use, import, export, generate, derive).
 * Here we define some backward compatibility support for uses stil using
 * the legacy symbols.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef MBEDTLS_PSA_CRYPTO_LEGACY_H
#define MBEDTLS_PSA_CRYPTO_LEGACY_H

#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR) //no-check-names
#if !defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC      1
#endif
#if !defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT   1
#endif
#if !defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT   1
#endif
#if !defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE 1
#endif
#if !defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE   1
#endif
#endif

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR) //no-check-names
#if !defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC      1
#endif
#if !defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT   1
#endif
#if !defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT   1
#endif
#if !defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE 1
#endif
#endif

#if defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR) //no-check-names
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_BASIC)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_BASIC
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_IMPORT)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_IMPORT
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_EXPORT)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_EXPORT
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_GENERATE)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_GENERATE
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_DERIVE)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_DERIVE
#endif
#endif

#if defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR) //no-check-names
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_BASIC)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_BASIC
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_IMPORT)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_IMPORT
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_EXPORT)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_EXPORT
#endif
#if !defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_GENERATE)
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_GENERATE
#endif
#endif

#endif /* MBEDTLS_PSA_CRYPTO_LEGACY_H */
