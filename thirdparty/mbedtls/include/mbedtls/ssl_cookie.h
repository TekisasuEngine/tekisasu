/**************************************************************************/
/*  ssl_cookie.h                                                          */
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
 * \file ssl_cookie.h
 *
 * \brief DTLS cookie callbacks implementation
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_SSL_COOKIE_H
#define MBEDTLS_SSL_COOKIE_H
#include "mbedtls/private_access.h"

#include "mbedtls/build_info.h"

#include "mbedtls/ssl.h"

#if !defined(MBEDTLS_USE_PSA_CRYPTO)
#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif
#endif /* !MBEDTLS_USE_PSA_CRYPTO */

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in mbedtls_config.h or define them on the compiler command line.
 * \{
 */
#ifndef MBEDTLS_SSL_COOKIE_TIMEOUT
#define MBEDTLS_SSL_COOKIE_TIMEOUT     60 /**< Default expiration delay of DTLS cookies, in seconds if HAVE_TIME, or in number of cookies issued */
#endif

/** \} name SECTION: Module settings */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Context for the default cookie functions.
 */
typedef struct mbedtls_ssl_cookie_ctx {
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    mbedtls_svc_key_id_t    MBEDTLS_PRIVATE(psa_hmac_key);  /*!< key id for the HMAC portion   */
    psa_algorithm_t         MBEDTLS_PRIVATE(psa_hmac_alg);  /*!< key algorithm for the HMAC portion   */
#else
    mbedtls_md_context_t    MBEDTLS_PRIVATE(hmac_ctx);   /*!< context for the HMAC portion   */
#endif /* MBEDTLS_USE_PSA_CRYPTO */
#if !defined(MBEDTLS_HAVE_TIME)
    unsigned long   MBEDTLS_PRIVATE(serial);     /*!< serial number for expiration   */
#endif
    unsigned long   MBEDTLS_PRIVATE(timeout);    /*!< timeout delay, in seconds if HAVE_TIME,
                                                    or in number of tickets issued */

#if !defined(MBEDTLS_USE_PSA_CRYPTO)
#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t MBEDTLS_PRIVATE(mutex);
#endif
#endif /* !MBEDTLS_USE_PSA_CRYPTO */
} mbedtls_ssl_cookie_ctx;

/**
 * \brief          Initialize cookie context
 */
void mbedtls_ssl_cookie_init(mbedtls_ssl_cookie_ctx *ctx);

/**
 * \brief          Setup cookie context (generate keys)
 */
int mbedtls_ssl_cookie_setup(mbedtls_ssl_cookie_ctx *ctx,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng);

/**
 * \brief          Set expiration delay for cookies
 *                 (Default MBEDTLS_SSL_COOKIE_TIMEOUT)
 *
 * \param ctx      Cookie context
 * \param delay    Delay, in seconds if HAVE_TIME, or in number of cookies
 *                 issued in the meantime.
 *                 0 to disable expiration (NOT recommended)
 */
void mbedtls_ssl_cookie_set_timeout(mbedtls_ssl_cookie_ctx *ctx, unsigned long delay);

/**
 * \brief          Free cookie context
 */
void mbedtls_ssl_cookie_free(mbedtls_ssl_cookie_ctx *ctx);

/**
 * \brief          Generate cookie, see \c mbedtls_ssl_cookie_write_t
 */
mbedtls_ssl_cookie_write_t mbedtls_ssl_cookie_write;

/**
 * \brief          Verify cookie, see \c mbedtls_ssl_cookie_write_t
 */
mbedtls_ssl_cookie_check_t mbedtls_ssl_cookie_check;

#ifdef __cplusplus
}
#endif

#endif /* ssl_cookie.h */
