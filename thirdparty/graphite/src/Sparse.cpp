/**************************************************************************/
/*  Sparse.cpp                                                            */
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

#include <cassert>
#include "inc/Sparse.h"
#include "inc/bits.h"

using namespace graphite2;

const sparse::chunk sparse::empty_chunk = {0,0};

sparse::~sparse() throw()
{
    if (m_array.map == &empty_chunk) return;
    free(m_array.values);
}


sparse::mapped_type sparse::operator [] (const key_type k) const throw()
{
    mapped_type         g = key_type(k/SIZEOF_CHUNK - m_nchunks) >> (sizeof k*8 - 1);
    const chunk &       c = m_array.map[g*k/SIZEOF_CHUNK];
    const mask_t        m = c.mask >> (SIZEOF_CHUNK - 1 - (k%SIZEOF_CHUNK));
    g *= m & 1;

    return g*m_array.values[g*(c.offset + bit_set_count(m >> 1))];
}


size_t sparse::capacity() const throw()
{
    size_t n = m_nchunks,
           s = 0;

    for (const chunk *ci=m_array.map; n; --n, ++ci)
        s += bit_set_count(ci->mask);

    return s;
}
