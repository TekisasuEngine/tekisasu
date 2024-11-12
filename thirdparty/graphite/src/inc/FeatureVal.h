/**************************************************************************/
/*  FeatureVal.h                                                          */
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
// Copyright 2010, SIL International, All rights reserved.

#pragma once
#include <cstring>
#include <cassert>
#include "inc/Main.h"
#include "inc/List.h"

namespace graphite2 {

class FeatureRef;
class FeatureMap;

class FeatureVal : public Vector<uint32>
{
public:
    FeatureVal() : m_pMap(0) { }
    FeatureVal(int num, const FeatureMap & pMap) : Vector<uint32>(num), m_pMap(&pMap) {}
    FeatureVal(const FeatureVal & rhs) : Vector<uint32>(rhs), m_pMap(rhs.m_pMap) {}

    FeatureVal & operator = (const FeatureVal & rhs) { Vector<uint32>::operator = (rhs); m_pMap = rhs.m_pMap; return *this; }

    bool operator ==(const FeatureVal & b) const
    {
        size_t n = size();
        if (n != b.size())      return false;

        for(const_iterator l = begin(), r = b.begin(); n && *l == *r; --n, ++l, ++r);

        return n == 0;
    }

    CLASS_NEW_DELETE
private:
    friend class FeatureRef;        //so that FeatureRefs can manipulate m_vec directly
    const FeatureMap* m_pMap;
};

typedef FeatureVal Features;

} // namespace graphite2


struct gr_feature_val : public graphite2::FeatureVal {};
