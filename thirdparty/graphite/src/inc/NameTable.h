/**************************************************************************/
/*  NameTable.h                                                           */
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

#include <graphite2/Segment.h>
#include "inc/TtfTypes.h"
#include "inc/locale2lcid.h"

namespace graphite2 {

class NameTable
{
    NameTable(const NameTable &);
    NameTable & operator = (const NameTable &);

public:
    NameTable(const void * data, size_t length, uint16 platfromId=3, uint16 encodingID = 1);
    ~NameTable() { free(const_cast<TtfUtil::Sfnt::FontNames *>(m_table)); }
    enum eNameFallback {
        eNoFallback = 0,
        eEnUSFallbackOnly = 1,
        eEnOrAnyFallback = 2
    };
    uint16 setPlatformEncoding(uint16 platfromId=3, uint16 encodingID = 1);
    void * getName(uint16 & languageId, uint16 nameId, gr_encform enc, uint32 & length);
    uint16 getLanguageId(const char * bcp47Locale);

    CLASS_NEW_DELETE
private:
    uint16 m_platformId;
    uint16 m_encodingId;
    uint16 m_languageCount;
    uint16 m_platformOffset; // offset of first NameRecord with for platform 3, encoding 1
    uint16 m_platformLastRecord;
    uint16 m_nameDataLength;
    const TtfUtil::Sfnt::FontNames * m_table;
    const uint8 * m_nameData;
    Locale2Lang m_locale2Lang;
};

} // namespace graphite2
