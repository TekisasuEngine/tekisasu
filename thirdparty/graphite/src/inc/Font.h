/**************************************************************************/
/*  Font.h                                                                */
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
#include <cassert>
#include "graphite2/Font.h"
#include "inc/Main.h"
#include "inc/Face.h"

namespace graphite2 {

#define INVALID_ADVANCE -1e38f      // can't be a static const because non-integral

class Font
{
public:
    Font(float ppm, const Face & face, const void * appFontHandle=0, const gr_font_ops * ops=0);
    virtual ~Font();

    float advance(unsigned short glyphid) const;
    float scale() const;
    bool isHinted() const;
    const Face & face() const;
    operator bool () const throw()  { return m_advances; }

    CLASS_NEW_DELETE;
private:
    gr_font_ops         m_ops;
    const void  * const m_appFontHandle;
    float             * m_advances;  // One advance per glyph in pixels. Nan if not defined
    const Face        & m_face;
    float               m_scale;      // scales from design units to ppm
    bool                m_hinted;

    Font(const Font&);
    Font& operator=(const Font&);
};

inline
float Font::advance(unsigned short glyphid) const
{
    if (m_advances[glyphid] == INVALID_ADVANCE)
        m_advances[glyphid] = (*m_ops.glyph_advance_x)(m_appFontHandle, glyphid);
    return m_advances[glyphid];
}

inline
float Font::scale() const
{
    return m_scale;
}

inline
bool Font::isHinted() const
{
    return m_hinted;
}

inline
const Face & Font::face() const
{
    return m_face;
}

} // namespace graphite2

struct gr_font : public graphite2::Font {};
