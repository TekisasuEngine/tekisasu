/**************************************************************************/
/*  check_crypto_config.h                                                 */
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
 * \file check_crypto_config.h
 *
 * \brief Consistency checks for PSA configuration options
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

/*
 * It is recommended to include this file from your crypto_config.h
 * in order to catch dependency issues early.
 */

#ifndef MBEDTLS_CHECK_CRYPTO_CONFIG_H
#define MBEDTLS_CHECK_CRYPTO_CONFIG_H

#if defined(PSA_WANT_ALG_CCM) && \
    !(defined(PSA_WANT_KEY_TYPE_AES) || \
    defined(PSA_WANT_KEY_TYPE_CAMELLIA))
#error "PSA_WANT_ALG_CCM defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_CMAC) && \
    !(defined(PSA_WANT_KEY_TYPE_AES) || \
    defined(PSA_WANT_KEY_TYPE_CAMELLIA) || \
    defined(PSA_WANT_KEY_TYPE_DES))
#error "PSA_WANT_ALG_CMAC defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_DETERMINISTIC_ECDSA) && \
    !(defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))
#error "PSA_WANT_ALG_DETERMINISTIC_ECDSA defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_ECDSA) && \
    !(defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY))
#error "PSA_WANT_ALG_ECDSA defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_GCM) && \
    !(defined(PSA_WANT_KEY_TYPE_AES) || \
    defined(PSA_WANT_KEY_TYPE_CAMELLIA))
#error "PSA_WANT_ALG_GCM defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT) && \
    !(defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY))
#error "PSA_WANT_ALG_RSA_PKCS1V15_CRYPT defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN) && \
    !(defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY))
#error "PSA_WANT_ALG_RSA_PKCS1V15_SIGN defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_OAEP) && \
    !(defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY))
#error "PSA_WANT_ALG_RSA_OAEP defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PSS) && \
    !(defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY))
#error "PSA_WANT_ALG_RSA_PSS defined, but not all prerequisites"
#endif

#if (defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE)) && \
    !defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY)
#error "PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_xxx defined, but not all prerequisites"
#endif

#if (defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE)) && \
    !defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY)
#error "PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_xxx defined, but not all prerequisites"
#endif

#if (defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_GENERATE)) && \
    !defined(PSA_WANT_KEY_TYPE_DH_PUBLIC_KEY)
#error "PSA_WANT_KEY_TYPE_DH_KEY_PAIR_xxx defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR)
#if defined(MBEDTLS_DEPRECATED_REMOVED)
#error "PSA_WANT_KEY_TYPE_ECC_KEY_PAIR is deprecated and will be removed in a \
    future version of Mbed TLS. Please switch to new PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_xxx \
    symbols, where xxx can be: USE, IMPORT, EXPORT, GENERATE, DERIVE"
#elif defined(MBEDTLS_DEPRECATED_WARNING)
#warning "PSA_WANT_KEY_TYPE_ECC_KEY_PAIR is deprecated and will be removed in a \
    future version of Mbed TLS. Please switch to new PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_xxx \
    symbols, where xxx can be: USE, IMPORT, EXPORT, GENERATE, DERIVE"
#endif /* MBEDTLS_DEPRECATED_WARNING */
#endif /* PSA_WANT_KEY_TYPE_ECC_KEY_PAIR */

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR)
#if defined(MBEDTLS_DEPRECATED_REMOVED)
#error "PSA_WANT_KEY_TYPE_RSA_KEY_PAIR is deprecated and will be removed in a \
    future version of Mbed TLS. Please switch to new PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_xxx \
    symbols, where xxx can be: USE, IMPORT, EXPORT, GENERATE, DERIVE"
#elif defined(MBEDTLS_DEPRECATED_WARNING)
#warning "PSA_WANT_KEY_TYPE_RSA_KEY_PAIR is deprecated and will be removed in a \
    future version of Mbed TLS. Please switch to new PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_xxx \
    symbols, where xxx can be: USE, IMPORT, EXPORT, GENERATE, DERIVE"
#endif /* MBEDTLS_DEPRECATED_WARNING */
#endif /* PSA_WANT_KEY_TYPE_RSA_KEY_PAIR */

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_DERIVE)
#error "PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_DERIVE defined, but feature is not supported"
#endif

#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_DERIVE)
#error "PSA_WANT_KEY_TYPE_DH_KEY_PAIR_DERIVE defined, but feature is not supported"
#endif

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && defined(MBEDTLS_USE_PSA_CRYPTO) && \
    !(defined(PSA_WANT_ALG_SHA_1) || defined(PSA_WANT_ALG_SHA_256) || defined(PSA_WANT_ALG_SHA_512))
#error "MBEDTLS_SSL_PROTO_TLS1_2 defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS) && \
    !defined(PSA_WANT_ALG_SHA_256)
#error "PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS defined, but not all prerequisites"
#endif

#endif /* MBEDTLS_CHECK_CRYPTO_CONFIG_H */
