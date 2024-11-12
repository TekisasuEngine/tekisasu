/**************************************************************************/
/*  vec3ba_sycl.h                                                         */
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

#include "../sys/alloc.h"
#include "emath.h"
#include "../simd/sse.h"

namespace embree
{
  ////////////////////////////////////////////////////////////////////////////////
  /// SSE Vec3ba Type
  ////////////////////////////////////////////////////////////////////////////////

  struct __aligned(16) Vec3ba
  {
    //ALIGNED_STRUCT_(16);
    
    struct { bool x,y,z; };

    typedef bool Scalar;
    enum { N = 3 };

    ////////////////////////////////////////////////////////////////////////////////
    /// Constructors, Assignment & Cast Operators
    ////////////////////////////////////////////////////////////////////////////////

    __forceinline Vec3ba( ) {}
    //__forceinline Vec3ba( const __m128  input ) : m128(input) {}

    __forceinline Vec3ba( const Vec3ba& other ) : x(other.x), y(other.y), z(other.z) {}
    __forceinline Vec3ba& operator =(const Vec3ba& other) { x = other.x; y = other.y; z = other.z; return *this; }

    __forceinline explicit Vec3ba( bool a ) : x(a), y(a), z(a) {}
    __forceinline Vec3ba( bool a, bool b, bool c) : x(a), y(b), z(c) {}

    //__forceinline operator const __m128&() const { return m128; }
    //__forceinline operator       __m128&()       { return m128; }

    ////////////////////////////////////////////////////////////////////////////////
    /// Constants
    ////////////////////////////////////////////////////////////////////////////////

    __forceinline Vec3ba( FalseTy ) : x(false), y(false), z(false) {}
    __forceinline Vec3ba( TrueTy  ) : x(true),  y(true),  z(true)  {}

    ////////////////////////////////////////////////////////////////////////////////
    /// Array Access
    ////////////////////////////////////////////////////////////////////////////////

    //__forceinline const int& operator []( const size_t index ) const { assert(index < 3); return (&x)[index]; }
    //__forceinline       int& operator []( const size_t index )       { assert(index < 3); return (&x)[index]; }
  };


  ////////////////////////////////////////////////////////////////////////////////
  /// Unary Operators
  ////////////////////////////////////////////////////////////////////////////////

  __forceinline Vec3ba operator !( const Vec3ba& a ) { return Vec3ba(!a.x,!a.y,!a.z); }

  ////////////////////////////////////////////////////////////////////////////////
  /// Binary Operators
  ////////////////////////////////////////////////////////////////////////////////

  __forceinline Vec3ba operator &( const Vec3ba& a, const Vec3ba& b ) { return Vec3ba(a.x & b.x, a.y & b.y, a.z & b.z); }
  __forceinline Vec3ba operator |( const Vec3ba& a, const Vec3ba& b ) { return Vec3ba(a.x | b.x, a.y | b.y, a.z | b.z); }
  __forceinline Vec3ba operator ^( const Vec3ba& a, const Vec3ba& b ) { return Vec3ba(a.x != b.x, a.y != b.y, a.z != b.z); }
  
  ////////////////////////////////////////////////////////////////////////////////
  /// Assignment Operators
  ////////////////////////////////////////////////////////////////////////////////
  
  __forceinline Vec3ba& operator &=( Vec3ba& a, const Vec3ba& b ) { return a = a & b; }
  __forceinline Vec3ba& operator |=( Vec3ba& a, const Vec3ba& b ) { return a = a | b; }
  __forceinline Vec3ba& operator ^=( Vec3ba& a, const Vec3ba& b ) { return a = a ^ b; }
  
  ////////////////////////////////////////////////////////////////////////////////
  /// Comparison Operators + Select
  ////////////////////////////////////////////////////////////////////////////////
  
  __forceinline bool operator ==( const Vec3ba& a, const Vec3ba& b ) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
  }
  __forceinline bool operator !=( const Vec3ba& a, const Vec3ba& b ) {
    return a.x != b.x || a.y != b.y || a.z != b.z;
  }
/*
  __forceinline bool operator < ( const Vec3ba& a, const Vec3ba& b ) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    if (a.z != b.z) return a.z < b.z;
    return false;
  }
*/
  ////////////////////////////////////////////////////////////////////////////////
  /// Reduction Operations
  ////////////////////////////////////////////////////////////////////////////////
    
  __forceinline bool reduce_and( const Vec3ba& a ) { return a.x & a.y & a.z; }
  __forceinline bool reduce_or ( const Vec3ba& a ) { return a.x | a.y | a.z; }

  __forceinline bool all       ( const Vec3ba& b ) { return reduce_and(b); }
  __forceinline bool any       ( const Vec3ba& b ) { return reduce_or(b); }
  __forceinline bool none      ( const Vec3ba& b ) { return !reduce_or(b); }

  ////////////////////////////////////////////////////////////////////////////////
  /// Output Operators
  ////////////////////////////////////////////////////////////////////////////////

  inline embree_ostream operator<<(embree_ostream cout, const Vec3ba& a) {
    return cout;
  }
}
