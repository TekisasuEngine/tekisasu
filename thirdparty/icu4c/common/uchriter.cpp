/**************************************************************************/
/*  uchriter.cpp                                                          */
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

// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
******************************************************************************
* Copyright (C) 1998-2012, International Business Machines Corporation and
* others. All Rights Reserved.
******************************************************************************
*/

#include "utypeinfo.h"  // for 'typeid' to work

#include "unicode/uchriter.h"
#include "unicode/ustring.h"
#include "unicode/utf16.h"
#include "ustr_imp.h"

U_NAMESPACE_BEGIN

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(UCharCharacterIterator)

UCharCharacterIterator::UCharCharacterIterator()
  : CharacterIterator(),
  text(nullptr)
{
    // never default construct!
}

UCharCharacterIterator::UCharCharacterIterator(ConstChar16Ptr textPtr,
                                               int32_t length)
  : CharacterIterator(textPtr != nullptr ? (length >= 0 ? length : u_strlen(textPtr)) : 0),
  text(textPtr)
{
}

UCharCharacterIterator::UCharCharacterIterator(ConstChar16Ptr textPtr,
                                               int32_t length,
                                               int32_t position)
  : CharacterIterator(textPtr != nullptr ? (length >= 0 ? length : u_strlen(textPtr)) : 0, position),
  text(textPtr)
{
}

UCharCharacterIterator::UCharCharacterIterator(ConstChar16Ptr textPtr,
                                               int32_t length,
                                               int32_t textBegin,
                                               int32_t textEnd,
                                               int32_t position)
  : CharacterIterator(textPtr != nullptr ? (length >= 0 ? length : u_strlen(textPtr)) : 0,
                      textBegin, textEnd, position),
  text(textPtr)
{
}

UCharCharacterIterator::UCharCharacterIterator(const UCharCharacterIterator& that)
: CharacterIterator(that),
  text(that.text)
{
}

UCharCharacterIterator&
UCharCharacterIterator::operator=(const UCharCharacterIterator& that) {
    CharacterIterator::operator=(that);
    text = that.text;
    return *this;
}

UCharCharacterIterator::~UCharCharacterIterator() {
}

bool
UCharCharacterIterator::operator==(const ForwardCharacterIterator& that) const {
    if (this == &that) {
        return true;
    }
    if (typeid(*this) != typeid(that)) {
        return false;
    }

    const UCharCharacterIterator&    realThat = static_cast<const UCharCharacterIterator&>(that);

    return text == realThat.text
        && textLength == realThat.textLength
        && pos == realThat.pos
        && begin == realThat.begin
        && end == realThat.end;
}

int32_t
UCharCharacterIterator::hashCode() const {
    return ustr_hashUCharsN(text, textLength) ^ pos ^ begin ^ end;
}

UCharCharacterIterator*
UCharCharacterIterator::clone() const {
    return new UCharCharacterIterator(*this);
}

char16_t
UCharCharacterIterator::first() {
    pos = begin;
    if(pos < end) {
        return text[pos];
    } else {
        return DONE;
    }
}

char16_t
UCharCharacterIterator::firstPostInc() {
    pos = begin;
    if(pos < end) {
        return text[pos++];
    } else {
        return DONE;
    }
}

char16_t
UCharCharacterIterator::last() {
    pos = end;
    if(pos > begin) {
        return text[--pos];
    } else {
        return DONE;
    }
}

char16_t
UCharCharacterIterator::setIndex(int32_t position) {
    if(position < begin) {
        pos = begin;
    } else if(position > end) {
        pos = end;
    } else {
        pos = position;
    }
    if(pos < end) {
        return text[pos];
    } else {
        return DONE;
    }
}

char16_t
UCharCharacterIterator::current() const {
    if (pos >= begin && pos < end) {
        return text[pos];
    } else {
        return DONE;
    }
}

char16_t
UCharCharacterIterator::next() {
    if (pos + 1 < end) {
        return text[++pos];
    } else {
        /* make current() return DONE */
        pos = end;
        return DONE;
    }
}

char16_t
UCharCharacterIterator::nextPostInc() {
    if (pos < end) {
        return text[pos++];
    } else {
        return DONE;
    }
}

UBool
UCharCharacterIterator::hasNext() {
    return (UBool)(pos < end ? true : false);
}

char16_t
UCharCharacterIterator::previous() {
    if (pos > begin) {
        return text[--pos];
    } else {
        return DONE;
    }
}

UBool
UCharCharacterIterator::hasPrevious() {
    return (UBool)(pos > begin ? true : false);
}

UChar32
UCharCharacterIterator::first32() {
    pos = begin;
    if(pos < end) {
        int32_t i = pos;
        UChar32 c;
        U16_NEXT(text, i, end, c);
        return c;
    } else {
        return DONE;
    }
}

UChar32
UCharCharacterIterator::first32PostInc() {
    pos = begin;
    if(pos < end) {
        UChar32 c;
        U16_NEXT(text, pos, end, c);
        return c;
    } else {
        return DONE;
    }
}

UChar32
UCharCharacterIterator::last32() {
    pos = end;
    if(pos > begin) {
        UChar32 c;
        U16_PREV(text, begin, pos, c);
        return c;
    } else {
        return DONE;
    }
}

UChar32
UCharCharacterIterator::setIndex32(int32_t position) {
    if(position < begin) {
        position = begin;
    } else if(position > end) {
        position = end;
    }
    if(position < end) {
        U16_SET_CP_START(text, begin, position);
        int32_t i = this->pos = position;
        UChar32 c;
        U16_NEXT(text, i, end, c);
        return c;
    } else {
        this->pos = position;
        return DONE;
    }
}

UChar32
UCharCharacterIterator::current32() const {
    if (pos >= begin && pos < end) {
        UChar32 c;
        U16_GET(text, begin, pos, end, c);
        return c;
    } else {
        return DONE;
    }
}

UChar32
UCharCharacterIterator::next32() {
    if (pos < end) {
        U16_FWD_1(text, pos, end);
        if(pos < end) {
            int32_t i = pos;
            UChar32 c;
            U16_NEXT(text, i, end, c);
            return c;
        }
    }
    /* make current() return DONE */
    pos = end;
    return DONE;
}

UChar32
UCharCharacterIterator::next32PostInc() {
    if (pos < end) {
        UChar32 c;
        U16_NEXT(text, pos, end, c);
        return c;
    } else {
        return DONE;
    }
}

UChar32
UCharCharacterIterator::previous32() {
    if (pos > begin) {
        UChar32 c;
        U16_PREV(text, begin, pos, c);
        return c;
    } else {
        return DONE;
    }
}

int32_t
UCharCharacterIterator::move(int32_t delta, CharacterIterator::EOrigin origin) {
    switch(origin) {
    case kStart:
        pos = begin + delta;
        break;
    case kCurrent:
        pos += delta;
        break;
    case kEnd:
        pos = end + delta;
        break;
    default:
        break;
    }

    if(pos < begin) {
        pos = begin;
    } else if(pos > end) {
        pos = end;
    }

    return pos;
}

int32_t
UCharCharacterIterator::move32(int32_t delta, CharacterIterator::EOrigin origin) {
    // this implementation relies on the "safe" version of the UTF macros
    // (or the trustworthiness of the caller)
    switch(origin) {
    case kStart:
        pos = begin;
        if(delta > 0) {
            U16_FWD_N(text, pos, end, delta);
        }
        break;
    case kCurrent:
        if(delta > 0) {
            U16_FWD_N(text, pos, end, delta);
        } else {
            U16_BACK_N(text, begin, pos, -delta);
        }
        break;
    case kEnd:
        pos = end;
        if(delta < 0) {
            U16_BACK_N(text, begin, pos, -delta);
        }
        break;
    default:
        break;
    }

    return pos;
}

void UCharCharacterIterator::setText(ConstChar16Ptr newText,
                                     int32_t      newTextLength) {
    text = newText;
    if (newText == nullptr || newTextLength < 0) {
        newTextLength = 0;
    }
    end = textLength = newTextLength;
    pos = begin = 0;
}

void
UCharCharacterIterator::getText(UnicodeString& result) {
    result = UnicodeString(text, textLength);
}

U_NAMESPACE_END
