/**************************************************************************/
/*  stdfs_conditions.h                                                    */
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

// Copyright (c) 2017-2024, The Khronos Group Inc.
// Copyright (c) 2017 Valve Corporation
// Copyright (c) 2017 LunarG, Inc.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#ifndef _STDFS_CONDITIONS_H
#define _STDFS_CONDITIONS_H

// If the C++ macro is set to the version containing C++17, it must support
// the final C++17 package
#if __cplusplus >= 201703L
#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 1

#elif defined(_MSC_VER) && _MSC_VER >= 1900

#if defined(_HAS_CXX17) && _HAS_CXX17
// When MSC supports c++17 use <filesystem> package.
#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 1
#endif  // !_HAS_CXX17

// GCC supports the experimental filesystem items starting in GCC 6
#elif (__GNUC__ >= 6)
#define USE_EXPERIMENTAL_FS 1
#define USE_FINAL_FS 0

// If Clang, check for feature support
#elif defined(__clang__) && (__cpp_lib_filesystem || __cpp_lib_experimental_filesystem)
#if __cpp_lib_filesystem
#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 1
#else
#define USE_EXPERIMENTAL_FS 1
#define USE_FINAL_FS 0
#endif

// If all above fails, fall back to standard C++ and OS-specific items
#else
#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 0
#endif

#endif  // !_STDFS_CONDITIONS_H
