/**************************************************************************/
/*  debug.h                                                               */
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
 * \file debug.h
 *
 * \brief Functions for controlling and providing debug output from the library.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_DEBUG_H
#define MBEDTLS_DEBUG_H

#include "mbedtls/build_info.h"

#include "mbedtls/ssl.h"

#if defined(MBEDTLS_ECP_C)
#include "mbedtls/ecp.h"
#endif

#if defined(MBEDTLS_DEBUG_C)

#define MBEDTLS_DEBUG_STRIP_PARENS(...)   __VA_ARGS__

#define MBEDTLS_SSL_DEBUG_MSG(level, args)                    \
    mbedtls_debug_print_msg(ssl, level, __FILE__, __LINE__,    \
                            MBEDTLS_DEBUG_STRIP_PARENS args)

#define MBEDTLS_SSL_DEBUG_RET(level, text, ret)                \
    mbedtls_debug_print_ret(ssl, level, __FILE__, __LINE__, text, ret)

#define MBEDTLS_SSL_DEBUG_BUF(level, text, buf, len)           \
    mbedtls_debug_print_buf(ssl, level, __FILE__, __LINE__, text, buf, len)

#if defined(MBEDTLS_BIGNUM_C)
#define MBEDTLS_SSL_DEBUG_MPI(level, text, X)                  \
    mbedtls_debug_print_mpi(ssl, level, __FILE__, __LINE__, text, X)
#endif

#if defined(MBEDTLS_ECP_C)
#define MBEDTLS_SSL_DEBUG_ECP(level, text, X)                  \
    mbedtls_debug_print_ecp(ssl, level, __FILE__, __LINE__, text, X)
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
#if !defined(MBEDTLS_X509_REMOVE_INFO)
#define MBEDTLS_SSL_DEBUG_CRT(level, text, crt)                \
    mbedtls_debug_print_crt(ssl, level, __FILE__, __LINE__, text, crt)
#else
#define MBEDTLS_SSL_DEBUG_CRT(level, text, crt)       do { } while (0)
#endif /* MBEDTLS_X509_REMOVE_INFO */
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_ECDH_C)
#define MBEDTLS_SSL_DEBUG_ECDH(level, ecdh, attr)               \
    mbedtls_debug_printf_ecdh(ssl, level, __FILE__, __LINE__, ecdh, attr)
#endif

#else /* MBEDTLS_DEBUG_C */

#define MBEDTLS_SSL_DEBUG_MSG(level, args)            do { } while (0)
#define MBEDTLS_SSL_DEBUG_RET(level, text, ret)       do { } while (0)
#define MBEDTLS_SSL_DEBUG_BUF(level, text, buf, len)  do { } while (0)
#define MBEDTLS_SSL_DEBUG_MPI(level, text, X)         do { } while (0)
#define MBEDTLS_SSL_DEBUG_ECP(level, text, X)         do { } while (0)
#define MBEDTLS_SSL_DEBUG_CRT(level, text, crt)       do { } while (0)
#define MBEDTLS_SSL_DEBUG_ECDH(level, ecdh, attr)     do { } while (0)

#endif /* MBEDTLS_DEBUG_C */

/**
 * \def MBEDTLS_PRINTF_ATTRIBUTE
 *
 * Mark a function as having printf attributes, and thus enable checking
 * via -wFormat and other flags. This does nothing on builds with compilers
 * that do not support the format attribute
 *
 * Module:  library/debug.c
 * Caller:
 *
 * This module provides debugging functions.
 */
#if defined(__has_attribute)
#if __has_attribute(format)
#if defined(__MINGW32__) && __USE_MINGW_ANSI_STDIO == 1
#define MBEDTLS_PRINTF_ATTRIBUTE(string_index, first_to_check)    \
    __attribute__((__format__(gnu_printf, string_index, first_to_check)))
#else /* defined(__MINGW32__) && __USE_MINGW_ANSI_STDIO == 1 */
#define MBEDTLS_PRINTF_ATTRIBUTE(string_index, first_to_check)    \
    __attribute__((format(printf, string_index, first_to_check)))
#endif
#else /* __has_attribute(format) */
#define MBEDTLS_PRINTF_ATTRIBUTE(string_index, first_to_check)
#endif /* __has_attribute(format) */
#else /* defined(__has_attribute) */
#define MBEDTLS_PRINTF_ATTRIBUTE(string_index, first_to_check)
#endif

/**
 * \def MBEDTLS_PRINTF_SIZET
 *
 * MBEDTLS_PRINTF_xxx: Due to issues with older window compilers
 * and MinGW we need to define the printf specifier for size_t
 * and long long per platform.
 *
 * Module:  library/debug.c
 * Caller:
 *
 * This module provides debugging functions.
 */
#if (defined(__MINGW32__) && __USE_MINGW_ANSI_STDIO == 0) || (defined(_MSC_VER) && _MSC_VER < 1800)
   #include <inttypes.h>
   #define MBEDTLS_PRINTF_SIZET     PRIuPTR
   #define MBEDTLS_PRINTF_LONGLONG  "I64d"
#else \
    /* (defined(__MINGW32__)  && __USE_MINGW_ANSI_STDIO == 0) || (defined(_MSC_VER) && _MSC_VER < 1800) */
   #define MBEDTLS_PRINTF_SIZET     "zu"
   #define MBEDTLS_PRINTF_LONGLONG  "lld"
#endif \
    /* (defined(__MINGW32__)  && __USE_MINGW_ANSI_STDIO == 0) || (defined(_MSC_VER) && _MSC_VER < 1800) */

#if !defined(MBEDTLS_PRINTF_MS_TIME)
#include <inttypes.h>
#if !defined(PRId64)
#define MBEDTLS_PRINTF_MS_TIME MBEDTLS_PRINTF_LONGLONG
#else
#define MBEDTLS_PRINTF_MS_TIME PRId64
#endif
#endif /* MBEDTLS_PRINTF_MS_TIME */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Set the threshold error level to handle globally all debug output.
 *          Debug messages that have a level over the threshold value are
 *          discarded.
 *          (Default value: 0 = No debug )
 *
 * \param threshold     threshold level of messages to filter on. Messages at a
 *                      higher level will be discarded.
 *                          - Debug levels
 *                              - 0 No debug
 *                              - 1 Error
 *                              - 2 State change
 *                              - 3 Informational
 *                              - 4 Verbose
 */
void mbedtls_debug_set_threshold(int threshold);

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_DEBUG_H */
