/**************************************************************************/
/*  platform_time.h                                                       */
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
 * \file platform_time.h
 *
 * \brief Mbed TLS Platform time abstraction
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_PLATFORM_TIME_H
#define MBEDTLS_PLATFORM_TIME_H

#include "mbedtls/build_info.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The time_t datatype
 */
#if defined(MBEDTLS_PLATFORM_TIME_TYPE_MACRO)
typedef MBEDTLS_PLATFORM_TIME_TYPE_MACRO mbedtls_time_t;
#else
/* For time_t */
#include <time.h>
typedef time_t mbedtls_time_t;
#endif /* MBEDTLS_PLATFORM_TIME_TYPE_MACRO */

#if defined(MBEDTLS_PLATFORM_MS_TIME_TYPE_MACRO)
typedef MBEDTLS_PLATFORM_MS_TIME_TYPE_MACRO mbedtls_ms_time_t;
#else
#include <stdint.h>
#include <inttypes.h>
typedef int64_t mbedtls_ms_time_t;
#endif /* MBEDTLS_PLATFORM_MS_TIME_TYPE_MACRO */

/**
 * \brief   Get time in milliseconds.
 *
 * \return Monotonically-increasing current time in milliseconds.
 *
 * \note Define MBEDTLS_PLATFORM_MS_TIME_ALT to be able to provide an
 *       alternative implementation
 *
 * \warning This function returns a monotonically-increasing time value from a
 *          start time that will differ from platform to platform, and possibly
 *          from run to run of the process.
 *
 */
mbedtls_ms_time_t mbedtls_ms_time(void);

/*
 * The function pointers for time
 */
#if defined(MBEDTLS_PLATFORM_TIME_ALT)
extern mbedtls_time_t (*mbedtls_time)(mbedtls_time_t *time);

/**
 * \brief   Set your own time function pointer
 *
 * \param   time_func   the time function implementation
 *
 * \return              0
 */
int mbedtls_platform_set_time(mbedtls_time_t (*time_func)(mbedtls_time_t *time));
#else
#if defined(MBEDTLS_PLATFORM_TIME_MACRO)
#define mbedtls_time    MBEDTLS_PLATFORM_TIME_MACRO
#else
#define mbedtls_time   time
#endif /* MBEDTLS_PLATFORM_TIME_MACRO */
#endif /* MBEDTLS_PLATFORM_TIME_ALT */

#ifdef __cplusplus
}
#endif

#endif /* platform_time.h */
