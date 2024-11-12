/**************************************************************************/
/*  col4.h                                                                */
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

#include "emath.h"

namespace embree
{
  ////////////////////////////////////////////////////////////////////////////////
  /// RGBA Color Class
  ////////////////////////////////////////////////////////////////////////////////

  template<typename T> struct Col4
  {
    T r, g, b, a;

    ////////////////////////////////////////////////////////////////////////////////
    /// Construction
    ////////////////////////////////////////////////////////////////////////////////

    __forceinline Col4           ( )                   { }
    __forceinline Col4           ( const Col4& other ) { r = other.r; g = other.g; b = other.b; a = other.a; }
    __forceinline Col4& operator=( const Col4& other ) { r = other.r; g = other.g; b = other.b; a = other.a; return *this; }

    __forceinline explicit Col4 (const T& v) : r(v), g(v), b(v), a(v) {}
    __forceinline          Col4 (const T& r, const T& g, const T& b, const T& a) : r(r), g(g), b(b), a(a) {}

    ////////////////////////////////////////////////////////////////////////////////
    /// Constants
    ////////////////////////////////////////////////////////////////////////////////

    __forceinline Col4 (ZeroTy)   : r(zero)   , g(zero)   , b(zero)   , a(zero) {}
    __forceinline Col4 (OneTy)    : r(one)    , g(one)    , b(one)    , a(one) {}
    __forceinline Col4 (PosInfTy) : r(pos_inf), g(pos_inf), b(pos_inf), a(pos_inf) {}
    __forceinline Col4 (NegInfTy) : r(neg_inf), g(neg_inf), b(neg_inf), a(neg_inf) {}
  };

  /*! output operator */
  template<typename T> __forceinline embree_ostream operator<<(embree_ostream cout, const Col4<T>& a) {
    return cout << "(" << a.r << ", " << a.g << ", " << a.b << ", " << a.a << ")";
  }

  /*! default template instantiations */
  typedef Col4<unsigned char> Col4uc;
  typedef Col4<float        > Col4f;
}
