/**************************************************************************/
/*  Endian.h                                                              */
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
// Copyright 2011, SIL International, All rights reserved.
/*
Description:
    A set of fast template based decoders for decoding values of any C integer
    type up to long int size laid out with most significant byte first or least
    significant byte first (aka big endian or little endian).  These are CPU
    byte order agnostic and will function the same regardless of the CPUs native
    byte order.

    Being template based means if the either le or be class is not used then
    template code of unused functions will not be instantiated by the compiler
    and thus shouldn't cause any overhead.
*/

#include <cstddef>

#pragma once


class be
{
    template<int S>
    inline static unsigned long int _peek(const unsigned char * p) {
        return _peek<S/2>(p) << (S/2)*8 | _peek<S/2>(p+S/2);
    }
public:
    template<typename T>
    inline static T peek(const void * p) {
        return T(_peek<sizeof(T)>(static_cast<const unsigned char *>(p)));
    }

    template<typename T>
    inline static T read(const unsigned char * &p) {
        const T r = T(_peek<sizeof(T)>(p));
        p += sizeof r;
        return r;
    }

    template<typename T>
    inline static T swap(const T x) {
        return T(_peek<sizeof(T)>(reinterpret_cast<const unsigned char *>(&x)));
    }

    template<typename T>
    inline static void skip(const unsigned char * &p, size_t n=1) {
        p += sizeof(T)*n;
    }
};

template<>
inline unsigned long int be::_peek<1>(const unsigned char * p) { return *p; }


class le
{
    template<int S>
    inline static unsigned long int _peek(const unsigned char * p) {
        return _peek<S/2>(p) | _peek<S/2>(p+S/2)  << (S/2)*8;
    }
public:
    template<typename T>
    inline static T peek(const void * p) {
        return T(_peek<sizeof(T)>(static_cast<const unsigned char *>(p)));
    }

    template<typename T>
    inline static T read(const unsigned char * &p) {
        const T r = T(_peek<sizeof(T)>(p));
        p += sizeof r;
        return r;
    }

    template<typename T>
    inline static T swap(const T x) {
        return T(_peek<sizeof(T)>(reinterpret_cast<const unsigned char *>(&x)));
    }

    template<typename T>
    inline static void skip(const unsigned char * &p, size_t n=1) {
        p += sizeof(T)*n;
    }
};

template<>
inline unsigned long int le::_peek<1>(const unsigned char * p) { return *p; }
