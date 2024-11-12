/**************************************************************************/
/*  ssl_ciphersuites_internal.h                                           */
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
 * \file ssl_ciphersuites_internal.h
 *
 * \brief Internal part of the public "ssl_ciphersuites.h".
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_SSL_CIPHERSUITES_INTERNAL_H
#define MBEDTLS_SSL_CIPHERSUITES_INTERNAL_H

#include "mbedtls/pk.h"

#if defined(MBEDTLS_PK_C)
mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_pk_alg(const mbedtls_ssl_ciphersuite_t *info);
#if defined(MBEDTLS_USE_PSA_CRYPTO)
psa_algorithm_t mbedtls_ssl_get_ciphersuite_sig_pk_psa_alg(const mbedtls_ssl_ciphersuite_t *info);
psa_key_usage_t mbedtls_ssl_get_ciphersuite_sig_pk_psa_usage(const mbedtls_ssl_ciphersuite_t *info);
#endif /* MBEDTLS_USE_PSA_CRYPTO */
mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_alg(const mbedtls_ssl_ciphersuite_t *info);
#endif /* MBEDTLS_PK_C */

int mbedtls_ssl_ciphersuite_uses_ec(const mbedtls_ssl_ciphersuite_t *info);
int mbedtls_ssl_ciphersuite_uses_psk(const mbedtls_ssl_ciphersuite_t *info);

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PFS_ENABLED)
static inline int mbedtls_ssl_ciphersuite_has_pfs(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECJPAKE:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PFS_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_NON_PFS_ENABLED)
static inline int mbedtls_ssl_ciphersuite_no_pfs(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_PSK:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_NON_PFS_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_ecdh(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_ECDH_ENABLED */

static inline int mbedtls_ssl_ciphersuite_cert_req_allowed(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return 1;

        default:
            return 0;
    }
}

static inline int mbedtls_ssl_ciphersuite_uses_srv_cert(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return 1;

        default:
            return 0;
    }
}

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_DHE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_dhe(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_DHE_ENABLED) */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_ECDHE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_ecdhe(const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_ECDHE_ENABLED) */

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_SERVER_SIGNATURE_ENABLED)
static inline int mbedtls_ssl_ciphersuite_uses_server_signature(
    const mbedtls_ssl_ciphersuite_t *info)
{
    switch (info->MBEDTLS_PRIVATE(key_exchange)) {
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return 1;

        default:
            return 0;
    }
}
#endif /* MBEDTLS_KEY_EXCHANGE_WITH_SERVER_SIGNATURE_ENABLED */

#endif /* MBEDTLS_SSL_CIPHERSUITES_INTERNAL_H */
