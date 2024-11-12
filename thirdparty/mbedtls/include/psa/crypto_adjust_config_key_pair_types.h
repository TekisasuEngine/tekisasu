/**************************************************************************/
/*  crypto_adjust_config_key_pair_types.h                                 */
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
 * \file psa/crypto_adjust_config_key_pair_types.h
 * \brief Adjust PSA configuration for key pair types.
 *
 * See docs/proposed/psa-conditional-inclusion-c.md.
 * - Support non-basic operations in a keypair type implicitly enables basic
 *   support for that keypair type.
 * - Support for a keypair type implicitly enables the corresponding public
 *   key type.
 * - Basic support for a keypair type implicilty enables import/export support
 *   for that keypair type. Warning: this is implementation-specific (mainly
 *   for the benefit of testing) and may change in the future!
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef PSA_CRYPTO_ADJUST_KEYPAIR_TYPES_H
#define PSA_CRYPTO_ADJUST_KEYPAIR_TYPES_H

/*****************************************************************
 * ANYTHING -> BASIC
 ****************************************************************/

#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE) || \
    defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC 1
#endif

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE) || \
    defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_DERIVE)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC 1
#endif

#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_GENERATE) || \
    defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_DERIVE)
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC 1
#endif

/*****************************************************************
 * BASIC -> corresponding PUBLIC
 ****************************************************************/

#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY 1
#endif

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY 1
#endif

#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_DH_PUBLIC_KEY 1
#endif

/*****************************************************************
 * BASIC -> IMPORT+EXPORT
 *
 * (Implementation-specific, may change in the future.)
 ****************************************************************/

/* Even though KEY_PAIR symbols' feature several level of support (BASIC, IMPORT,
 * EXPORT, GENERATE, DERIVE) we're not planning to have support only for BASIC
 * without IMPORT/EXPORT since these last 2 features are strongly used in tests.
 * In general it is allowed to include more feature than what is strictly
 * requested.
 * As a consequence IMPORT and EXPORT features will be automatically enabled
 * as soon as the BASIC one is. */
#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT 1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT 1
#endif

#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT 1
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT 1
#endif

#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC)
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT 1
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT 1
#endif

#endif /* PSA_CRYPTO_ADJUST_KEYPAIR_TYPES_H */
