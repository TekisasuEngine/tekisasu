/**************************************************************************/
/*  Font.cpp                                                              */
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

#include "inc/Face.h"
#include "inc/Font.h"
#include "inc/GlyphCache.h"

using namespace graphite2;

Font::Font(float ppm, const Face & f, const void * appFontHandle, const gr_font_ops * ops)
: m_appFontHandle(appFontHandle ? appFontHandle : this),
  m_face(f),
  m_scale(ppm / f.glyphs().unitsPerEm()),
  m_hinted(appFontHandle && ops && (ops->glyph_advance_x || ops->glyph_advance_y))
{
    memset(&m_ops, 0, sizeof m_ops);
    if (m_hinted && ops)
        memcpy(&m_ops, ops, min(sizeof m_ops, ops->size));
    else
        m_ops.glyph_advance_x = &Face::default_glyph_advance;

    size_t nGlyphs = f.glyphs().numGlyphs();
    m_advances = gralloc<float>(nGlyphs);
    if (m_advances)
    {
        for (float *advp = m_advances; nGlyphs; --nGlyphs, ++advp)
            *advp = INVALID_ADVANCE;
    }
}


/*virtual*/ Font::~Font()
{
    free(m_advances);
}
