/**************************************************************************/
/*  pk_wrap.h                                                             */
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
 * \file pk_wrap.h
 *
 * \brief Public Key abstraction layer: wrapper functions
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef MBEDTLS_PK_WRAP_H
#define MBEDTLS_PK_WRAP_H

#include "mbedtls/build_info.h"

#include "mbedtls/pk.h"

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#endif

struct mbedtls_pk_info_t {
    /** Public key type */
    mbedtls_pk_type_t type;

    /** Type name */
    const char *name;

    /** Get key size in bits */
    size_t (*get_bitlen)(mbedtls_pk_context *pk);

    /** Tell if the context implements this type (e.g. ECKEY can do ECDSA) */
    int (*can_do)(mbedtls_pk_type_t type);

    /** Verify signature */
    int (*verify_func)(mbedtls_pk_context *pk, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len);

    /** Make signature */
    int (*sign_func)(mbedtls_pk_context *pk, mbedtls_md_type_t md_alg,
                     const unsigned char *hash, size_t hash_len,
                     unsigned char *sig, size_t sig_size, size_t *sig_len,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng);

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    /** Verify signature (restartable) */
    int (*verify_rs_func)(mbedtls_pk_context *pk, mbedtls_md_type_t md_alg,
                          const unsigned char *hash, size_t hash_len,
                          const unsigned char *sig, size_t sig_len,
                          void *rs_ctx);

    /** Make signature (restartable) */
    int (*sign_rs_func)(mbedtls_pk_context *pk, mbedtls_md_type_t md_alg,
                        const unsigned char *hash, size_t hash_len,
                        unsigned char *sig, size_t sig_size, size_t *sig_len,
                        int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng, void *rs_ctx);
#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

    /** Decrypt message */
    int (*decrypt_func)(mbedtls_pk_context *pk, const unsigned char *input, size_t ilen,
                        unsigned char *output, size_t *olen, size_t osize,
                        int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng);

    /** Encrypt message */
    int (*encrypt_func)(mbedtls_pk_context *pk, const unsigned char *input, size_t ilen,
                        unsigned char *output, size_t *olen, size_t osize,
                        int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng);

    /** Check public-private key pair */
    int (*check_pair_func)(mbedtls_pk_context *pub, mbedtls_pk_context *prv,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng);

    /** Allocate a new context */
    void * (*ctx_alloc_func)(void);

    /** Free the given context */
    void (*ctx_free_func)(void *ctx);

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    /** Allocate the restart context */
    void *(*rs_alloc_func)(void);

    /** Free the restart context */
    void (*rs_free_func)(void *rs_ctx);
#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

    /** Interface with the debug module */
    void (*debug_func)(mbedtls_pk_context *pk, mbedtls_pk_debug_item *items);

};
#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
/* Container for RSA-alt */
typedef struct {
    void *key;
    mbedtls_pk_rsa_alt_decrypt_func decrypt_func;
    mbedtls_pk_rsa_alt_sign_func sign_func;
    mbedtls_pk_rsa_alt_key_len_func key_len_func;
} mbedtls_rsa_alt_context;
#endif

#if defined(MBEDTLS_RSA_C)
extern const mbedtls_pk_info_t mbedtls_rsa_info;
#endif

#if defined(MBEDTLS_PK_HAVE_ECC_KEYS)
extern const mbedtls_pk_info_t mbedtls_eckey_info;
extern const mbedtls_pk_info_t mbedtls_eckeydh_info;
#endif

#if defined(MBEDTLS_PK_CAN_ECDSA_SOME)
extern const mbedtls_pk_info_t mbedtls_ecdsa_info;
#endif

#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
extern const mbedtls_pk_info_t mbedtls_rsa_alt_info;
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
extern const mbedtls_pk_info_t mbedtls_ecdsa_opaque_info;
extern const mbedtls_pk_info_t mbedtls_rsa_opaque_info;

#if defined(MBEDTLS_RSA_C)
int mbedtls_pk_psa_rsa_sign_ext(psa_algorithm_t psa_alg_md,
                                mbedtls_rsa_context *rsa_ctx,
                                const unsigned char *hash, size_t hash_len,
                                unsigned char *sig, size_t sig_size,
                                size_t *sig_len);
#endif /* MBEDTLS_RSA_C */

#endif /* MBEDTLS_USE_PSA_CRYPTO */

#endif /* MBEDTLS_PK_WRAP_H */
