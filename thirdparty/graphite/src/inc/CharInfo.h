/**************************************************************************/
/*  CharInfo.h                                                            */
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
#include "inc/Main.h"


namespace graphite2 {

class CharInfo
{

public:
    CharInfo() : m_char(0), m_before(-1), m_after(-1), m_base(0), m_featureid(0), m_break(0), m_flags(0) {}
    void init(int cid) { m_char = cid; }
    unsigned int unicodeChar() const { return m_char; }
    void feats(int offset) { m_featureid = offset; }
    int fid() const { return m_featureid; }
    int breakWeight() const { return m_break; }
    void breakWeight(int val) { m_break = val; }
    int after() const { return m_after; }
    void after(int val) { m_after = val; }
    int before() const { return m_before; }
    void before(int val) { m_before = val; }
    size_t base() const { return m_base; }
    void base(size_t offset) { m_base = offset; }
    void addflags(uint8 val) { m_flags |= val; }
    uint8 flags() const { return m_flags; }

    CLASS_NEW_DELETE
private:
    int m_char;     // Unicode character from character stream
    int m_before;   // slot index before us, comes before
    int m_after;    // slot index after us, comes after
    size_t  m_base; // offset into input string corresponding to this charinfo
    uint8 m_featureid;  // index into features list in the segment
    int8 m_break;   // breakweight coming from lb table
    uint8 m_flags;  // 0,1 segment split.
};

} // namespace graphite2

struct gr_char_info : public graphite2::CharInfo {};
