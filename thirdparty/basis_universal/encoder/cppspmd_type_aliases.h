/**************************************************************************/
/*  cppspmd_type_aliases.h                                                */
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

// cppspmd_type_aliases.h
// Do not include this file directly
//
// Copyright 2020-2021 Binomial LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#ifndef CPPSPMD_TYPES
#define CPPSPMD_TYPES

using exec_mask = CPPSPMD::exec_mask;

#if CPPSPMD_INT16
using vint16 = CPPSPMD::vint16;
using int16_lref = CPPSPMD::int16_lref;
using cint16_vref = CPPSPMD::cint16_vref;
using int16_vref = CPPSPMD::int16_vref;
using lint16 = CPPSPMD::lint16;
using vint16_vref = CPPSPMD::vint16_vref;
#else
using vint = CPPSPMD::vint;
using int_lref = CPPSPMD::int_lref;
using cint_vref = CPPSPMD::cint_vref;
using int_vref = CPPSPMD::int_vref;
using lint = CPPSPMD::lint;
using vint_vref = CPPSPMD::vint_vref;
#endif

using vbool = CPPSPMD::vbool;
using vfloat = CPPSPMD::vfloat;
using float_lref = CPPSPMD::float_lref;
using float_vref = CPPSPMD::float_vref;
using vfloat_vref = CPPSPMD::vfloat_vref;

#endif // CPPSPMD_TYPES
