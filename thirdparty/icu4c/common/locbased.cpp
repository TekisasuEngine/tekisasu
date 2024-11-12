/**************************************************************************/
/*  locbased.cpp                                                          */
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
**********************************************************************
* Copyright (c) 2004-2014, International Business Machines
* Corporation and others.  All Rights Reserved.
**********************************************************************
* Author: Alan Liu
* Created: January 16 2004
* Since: ICU 2.8
**********************************************************************
*/
#include "locbased.h"
#include "cstring.h"

U_NAMESPACE_BEGIN

Locale LocaleBased::getLocale(ULocDataLocaleType type, UErrorCode& status) const {
    const char* id = getLocaleID(type, status);
    return Locale(id != nullptr ? id : "");
}

const char* LocaleBased::getLocaleID(ULocDataLocaleType type, UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return nullptr;
    }

    switch(type) {
    case ULOC_VALID_LOCALE:
        return valid;
    case ULOC_ACTUAL_LOCALE:
        return actual;
    default:
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return nullptr;
    }
}

void LocaleBased::setLocaleIDs(const char* validID, const char* actualID) {
    if (validID != nullptr) {
      uprv_strncpy(valid, validID, ULOC_FULLNAME_CAPACITY);
      valid[ULOC_FULLNAME_CAPACITY-1] = 0; // always terminate
    }
    if (actualID != nullptr) {
      uprv_strncpy(actual, actualID, ULOC_FULLNAME_CAPACITY);
      actual[ULOC_FULLNAME_CAPACITY-1] = 0; // always terminate
    }
}

void LocaleBased::setLocaleIDs(const Locale& validID, const Locale& actualID) {
  uprv_strcpy(valid, validID.getName());
  uprv_strcpy(actual, actualID.getName());
}

U_NAMESPACE_END
