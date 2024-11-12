/**************************************************************************/
/*  rtcore_config.h                                                       */
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

// Copyright 2009-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#if !defined(EMBREE_SYCL_SUPPORT)
// #cmakedefine EMBREE_SYCL_SUPPORT
#endif

#define RTC_VERSION_MAJOR 4
#define RTC_VERSION_MINOR 3
#define RTC_VERSION_PATCH 1
#define RTC_VERSION 40301
#define RTC_VERSION_STRING "4.3.1"

#define RTC_MAX_INSTANCE_LEVEL_COUNT 1

// #cmakedefine EMBREE_GEOMETRY_INSTANCE_ARRAY
#if defined(EMBREE_GEOMETRY_INSTANCE_ARRAY)
  #define RTC_GEOMETRY_INSTANCE_ARRAY
#endif

// #cmakedefine01 EMBREE_SYCL_GEOMETRY_CALLBACK

#define EMBREE_MIN_WIDTH 0
#define RTC_MIN_WIDTH EMBREE_MIN_WIDTH

#if !defined(EMBREE_STATIC_LIB)
#define EMBREE_STATIC_LIB
#endif
// #cmakedefine EMBREE_API_NAMESPACE

#if defined(EMBREE_API_NAMESPACE)
#  define RTC_NAMESPACE
#  define RTC_NAMESPACE_BEGIN namespace {
#  define RTC_NAMESPACE_END }
#  define RTC_NAMESPACE_USE using namespace;
#  define RTC_API_EXTERN_C
#  undef EMBREE_API_NAMESPACE
#else
#  define RTC_NAMESPACE_BEGIN
#  define RTC_NAMESPACE_END
#  define RTC_NAMESPACE_USE
#  if defined(__cplusplus)
#    define RTC_API_EXTERN_C extern "C"
#  else
#    define RTC_API_EXTERN_C
#  endif
#endif

#if defined(ISPC)
#  define RTC_API_IMPORT extern "C" unmasked
#  define RTC_API_EXPORT extern "C" unmasked
#elif defined(EMBREE_STATIC_LIB)
#  define RTC_API_IMPORT RTC_API_EXTERN_C
#  define RTC_API_EXPORT RTC_API_EXTERN_C
#elif defined(_WIN32)
#  define RTC_API_IMPORT RTC_API_EXTERN_C __declspec(dllimport)
#  define RTC_API_EXPORT RTC_API_EXTERN_C __declspec(dllexport)
#else
#  define RTC_API_IMPORT RTC_API_EXTERN_C
#  define RTC_API_EXPORT RTC_API_EXTERN_C __attribute__ ((visibility ("default")))
#endif

#if defined(RTC_EXPORT_API)
#  define RTC_API RTC_API_EXPORT
#else
#  define RTC_API RTC_API_IMPORT
#endif

#if defined(ISPC)
#  define RTC_SYCL_INDIRECTLY_CALLABLE
#elif defined(__SYCL_DEVICE_ONLY__)
#  define RTC_SYCL_INDIRECTLY_CALLABLE [[intel::device_indirectly_callable]] SYCL_EXTERNAL
#  define RTC_SYCL_API                 SYCL_EXTERNAL
#else
#  define RTC_SYCL_INDIRECTLY_CALLABLE
#  define RTC_SYCL_API RTC_API
#endif

