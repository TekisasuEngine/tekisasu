/**************************************************************************/
/*  bits.h                                                                */
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

// SPDX-License-Identifier: MIT OR MPL-2.0 OR LGPL-2.1-or-later OR GPL-2.0-or-later
// Copyright 2012, SIL International, All rights reserved.

#pragma once

namespace graphite2
{


#if defined GRAPHITE2_BUILTINS && (defined __GNUC__ || defined __clang__)

template<typename T>
inline unsigned int bit_set_count(T v)
{
    return __builtin_popcount(v);
}

template<>
inline unsigned int bit_set_count(int16 v)
{
    return __builtin_popcount(static_cast<uint16>(v));
}

template<>
inline unsigned int bit_set_count(int8 v)
{
    return __builtin_popcount(static_cast<uint8>(v));
}

template<>
inline unsigned int bit_set_count(unsigned long v)
{
    return __builtin_popcountl(v);
}

template<>
inline unsigned int bit_set_count(signed long v)
{
    return __builtin_popcountl(v);
}

template<>
inline unsigned int bit_set_count(unsigned long long v)
{
    return __builtin_popcountll(v);
}

template<>
inline unsigned int bit_set_count(signed long long v)
{
    return __builtin_popcountll(v);
}

#else

template<typename T>
inline unsigned int bit_set_count(T v)
{
	static size_t const ONES = ~0;

	v = v - ((v >> 1) & T(ONES/3));                      // temp
    v = (v & T(ONES/15*3)) + ((v >> 2) & T(ONES/15*3));  // temp
    v = (v + (v >> 4)) & T(ONES/255*15);                 // temp
    return (T)(v * T(ONES/255)) >> (sizeof(T)-1)*8;      // count
}

#endif

//TODO: Changed these to uintmax_t when we go to C++11
template<int S>
inline size_t _mask_over_val(size_t v)
{
    v = _mask_over_val<S/2>(v);
    v |= v >> S*4;
    return v;
}

//TODO: Changed these to uintmax_t when we go to C++11
template<>
inline size_t _mask_over_val<1>(size_t v)
{
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    return v;
}

template<typename T>
inline T mask_over_val(T v)
{
    return T(_mask_over_val<sizeof(T)>(v));
}

template<typename T>
inline unsigned long next_highest_power2(T v)
{
    return _mask_over_val<sizeof(T)>(v-1)+1;
}

template<typename T>
inline unsigned int log_binary(T v)
{
    return bit_set_count(mask_over_val(v))-1;
}

template<typename T>
inline T has_zero(const T x)
{
    return (x - T(~T(0)/255)) & ~x & T(~T(0)/255*128);
}

template<typename T>
inline T zero_bytes(const T x, unsigned char n)
{
    const T t = T(~T(0)/255*n);
    return T((has_zero(x^t) >> 7)*n);
}

#if 0
inline float float_round(float x, uint32 m)
{
    *reinterpret_cast<unsigned int *>(&x) &= m;
    return *reinterpret_cast<float *>(&x);
}
#endif

}
