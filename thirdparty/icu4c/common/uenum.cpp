/**************************************************************************/
/*  uenum.cpp                                                             */
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
*******************************************************************************
*
*   Copyright (C) 2002-2012, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  uenum.c
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:2
*
*   created on: 2002jul08
*   created by: Vladimir Weinstein
*/

#include "unicode/putil.h"
#include "uenumimp.h"
#include "cmemory.h"

/* Layout of the baseContext buffer. */
typedef struct {
    int32_t len;  /* number of bytes available starting at 'data' */
    char    data; /* actual data starts here */
} _UEnumBuffer;

/* Extra bytes to allocate in the baseContext buffer. */
static const int32_t PAD = 8;

/* Return a pointer to the baseContext buffer, possibly allocating
   or reallocating it if at least 'capacity' bytes are not available. */
static void* _getBuffer(UEnumeration* en, int32_t capacity) {

    if (en->baseContext != nullptr) {
        if (((_UEnumBuffer*) en->baseContext)->len < capacity) {
            capacity += PAD;
            en->baseContext = uprv_realloc(en->baseContext,
                                           sizeof(int32_t) + capacity);
            if (en->baseContext == nullptr) {
                return nullptr;
            }
            ((_UEnumBuffer*) en->baseContext)->len = capacity;
        }
    } else {
        capacity += PAD;
        en->baseContext = uprv_malloc(sizeof(int32_t) + capacity);
        if (en->baseContext == nullptr) {
            return nullptr;
        }
        ((_UEnumBuffer*) en->baseContext)->len = capacity;
    }
    
    return (void*) & ((_UEnumBuffer*) en->baseContext)->data;
}

U_CAPI void U_EXPORT2
uenum_close(UEnumeration* en)
{
    if (en) {
        if (en->close != nullptr) {
            if (en->baseContext) {
                uprv_free(en->baseContext);
            }
            en->close(en);
        } else { /* this seems dangerous, but we better kill the object */
            uprv_free(en);
        }
    }
}

U_CAPI int32_t U_EXPORT2
uenum_count(UEnumeration* en, UErrorCode* status)
{
    if (!en || U_FAILURE(*status)) {
        return -1;
    }
    if (en->count != nullptr) {
        return en->count(en, status);
    } else {
        *status = U_UNSUPPORTED_ERROR;
        return -1;
    }
}

/* Don't call this directly. Only uenum_unext should be calling this. */
U_CAPI const char16_t* U_EXPORT2
uenum_unextDefault(UEnumeration* en,
            int32_t* resultLength,
            UErrorCode* status)
{
    char16_t *ustr = nullptr;
    int32_t len = 0;
    if (en->next != nullptr) {
        const char *cstr = en->next(en, &len, status);
        if (cstr != nullptr) {
            ustr = (char16_t*) _getBuffer(en, (len+1) * sizeof(char16_t));
            if (ustr == nullptr) {
                *status = U_MEMORY_ALLOCATION_ERROR;
            } else {
                u_charsToUChars(cstr, ustr, len+1);
            }
        }
    } else {
        *status = U_UNSUPPORTED_ERROR;
    }
    if (resultLength) {
        *resultLength = len;
    }
    return ustr;
}

/* Don't call this directly. Only uenum_next should be calling this. */
U_CAPI const char* U_EXPORT2
uenum_nextDefault(UEnumeration* en,
            int32_t* resultLength,
            UErrorCode* status)
{
    if (en->uNext != nullptr) {
        char *tempCharVal;
        const char16_t *tempUCharVal = en->uNext(en, resultLength, status);
        if (tempUCharVal == nullptr) {
            return nullptr;
        }
        tempCharVal = (char*)
            _getBuffer(en, (*resultLength+1) * sizeof(char));
        if (!tempCharVal) {
            *status = U_MEMORY_ALLOCATION_ERROR;
            return nullptr;
        }
        u_UCharsToChars(tempUCharVal, tempCharVal, *resultLength + 1);
        return tempCharVal;
    } else {
        *status = U_UNSUPPORTED_ERROR;
        return nullptr;
    }
}

U_CAPI const char16_t* U_EXPORT2
uenum_unext(UEnumeration* en,
            int32_t* resultLength,
            UErrorCode* status)
{
    if (!en || U_FAILURE(*status)) {
        return nullptr;
    }
    if (en->uNext != nullptr) {
        return en->uNext(en, resultLength, status);
    } else {
        *status = U_UNSUPPORTED_ERROR;
        return nullptr;
    }
}

U_CAPI const char* U_EXPORT2
uenum_next(UEnumeration* en,
          int32_t* resultLength,
          UErrorCode* status)
{
    if (!en || U_FAILURE(*status)) {
        return nullptr;
    }
    if (en->next != nullptr) {
        if (resultLength != nullptr) {
            return en->next(en, resultLength, status);
        }
        else {
            int32_t dummyLength=0;
            return en->next(en, &dummyLength, status);
        }
    } else {
        *status = U_UNSUPPORTED_ERROR;
        return nullptr;
    }
}

U_CAPI void U_EXPORT2
uenum_reset(UEnumeration* en, UErrorCode* status)
{
    if (!en || U_FAILURE(*status)) {
        return;
    }
    if (en->reset != nullptr) {
        en->reset(en, status);
    } else {
        *status = U_UNSUPPORTED_ERROR;
    }
}
