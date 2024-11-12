/**************************************************************************/
/*  padlock.h                                                             */
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
 * \file padlock.h
 *
 * \brief VIA PadLock ACE for HW encryption/decryption supported by some
 *        processors
 *
 * \warning These functions are only for internal use by other library
 *          functions; you must not call them directly.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_PADLOCK_H
#define MBEDTLS_PADLOCK_H

#include "mbedtls/build_info.h"

#include "mbedtls/aes.h"

#define MBEDTLS_ERR_PADLOCK_DATA_MISALIGNED               -0x0030  /**< Input data should be aligned. */

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define MBEDTLS_HAVE_ASAN
#endif
#endif

/*
 * - `padlock` is implements with GNUC assembly for x86 target.
 * - Some versions of ASan result in errors about not enough registers.
 */
#if defined(MBEDTLS_PADLOCK_C) && \
    defined(__GNUC__) && defined(MBEDTLS_ARCH_IS_X86) && \
    defined(MBEDTLS_HAVE_ASM) && \
    !defined(MBEDTLS_HAVE_ASAN)

#define MBEDTLS_VIA_PADLOCK_HAVE_CODE

#include <stdint.h>

#define MBEDTLS_PADLOCK_RNG 0x000C
#define MBEDTLS_PADLOCK_ACE 0x00C0
#define MBEDTLS_PADLOCK_PHE 0x0C00
#define MBEDTLS_PADLOCK_PMM 0x3000

#define MBEDTLS_PADLOCK_ALIGN16(x) (uint32_t *) (16 + ((int32_t) (x) & ~15))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Internal PadLock detection routine
 *
 * \note           This function is only for internal use by other library
 *                 functions; you must not call it directly.
 *
 * \param feature  The feature to detect
 *
 * \return         non-zero if CPU has support for the feature, 0 otherwise
 */
int mbedtls_padlock_has_support(int feature);

/**
 * \brief          Internal PadLock AES-ECB block en(de)cryption
 *
 * \note           This function is only for internal use by other library
 *                 functions; you must not call it directly.
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 *
 * \return         0 if success, 1 if operation failed
 */
int mbedtls_padlock_xcryptecb(mbedtls_aes_context *ctx,
                              int mode,
                              const unsigned char input[16],
                              unsigned char output[16]);

/**
 * \brief          Internal PadLock AES-CBC buffer en(de)cryption
 *
 * \note           This function is only for internal use by other library
 *                 functions; you must not call it directly.
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if success, 1 if operation failed
 */
int mbedtls_padlock_xcryptcbc(mbedtls_aes_context *ctx,
                              int mode,
                              size_t length,
                              unsigned char iv[16],
                              const unsigned char *input,
                              unsigned char *output);

#ifdef __cplusplus
}
#endif

#endif /* HAVE_X86  */

#endif /* padlock.h */
