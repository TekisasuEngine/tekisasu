/**************************************************************************/
/*  ssl_debug_helpers.h                                                   */
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
 * \file ssl_debug_helpers.h
 *
 * \brief Automatically generated helper functions for debugging
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef MBEDTLS_SSL_DEBUG_HELPERS_H
#define MBEDTLS_SSL_DEBUG_HELPERS_H

#include "common.h"

#if defined(MBEDTLS_DEBUG_C)

#include "mbedtls/ssl.h"
#include "ssl_misc.h"


const char *mbedtls_ssl_states_str(mbedtls_ssl_states in);

#if defined(MBEDTLS_SSL_EARLY_DATA) && defined(MBEDTLS_SSL_CLI_C)
const char *mbedtls_ssl_early_data_status_str(mbedtls_ssl_early_data_status in);
const char *mbedtls_ssl_early_data_state_str(mbedtls_ssl_early_data_state in);
#endif

const char *mbedtls_ssl_protocol_version_str(mbedtls_ssl_protocol_version in);

const char *mbedtls_tls_prf_types_str(mbedtls_tls_prf_types in);

const char *mbedtls_ssl_key_export_type_str(mbedtls_ssl_key_export_type in);

const char *mbedtls_ssl_sig_alg_to_str(uint16_t in);

const char *mbedtls_ssl_named_group_to_str(uint16_t in);

const char *mbedtls_ssl_get_extension_name(unsigned int extension_type);

void mbedtls_ssl_print_extensions(const mbedtls_ssl_context *ssl,
                                  int level, const char *file, int line,
                                  int hs_msg_type, uint32_t extensions_mask,
                                  const char *extra);

void mbedtls_ssl_print_extension(const mbedtls_ssl_context *ssl,
                                 int level, const char *file, int line,
                                 int hs_msg_type, unsigned int extension_type,
                                 const char *extra_msg0, const char *extra_msg1);

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
void mbedtls_ssl_print_ticket_flags(const mbedtls_ssl_context *ssl,
                                    int level, const char *file, int line,
                                    unsigned int flags);
#endif /* MBEDTLS_SSL_PROTO_TLS1_3 && MBEDTLS_SSL_SESSION_TICKETS */

#define MBEDTLS_SSL_PRINT_EXTS(level, hs_msg_type, extensions_mask)            \
    mbedtls_ssl_print_extensions(ssl, level, __FILE__, __LINE__,       \
                                 hs_msg_type, extensions_mask, NULL)

#define MBEDTLS_SSL_PRINT_EXT(level, hs_msg_type, extension_type, extra)      \
    mbedtls_ssl_print_extension(ssl, level, __FILE__, __LINE__,        \
                                hs_msg_type, extension_type,           \
                                extra, NULL)

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
#define MBEDTLS_SSL_PRINT_TICKET_FLAGS(level, flags)             \
    mbedtls_ssl_print_ticket_flags(ssl, level, __FILE__, __LINE__, flags)
#endif

#else

#define MBEDTLS_SSL_PRINT_EXTS(level, hs_msg_type, extension_mask)

#define MBEDTLS_SSL_PRINT_EXT(level, hs_msg_type, extension_type, extra)

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
#define MBEDTLS_SSL_PRINT_TICKET_FLAGS(level, flags)
#endif

#endif /* MBEDTLS_DEBUG_C */

#endif /* MBEDTLS_SSL_DEBUG_HELPERS_H */
