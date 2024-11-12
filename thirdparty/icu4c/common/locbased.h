/**************************************************************************/
/*  locbased.h                                                            */
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
#ifndef LOCBASED_H
#define LOCBASED_H

#include "unicode/locid.h"
#include "unicode/uobject.h"

/**
 * Macro to declare a locale LocaleBased wrapper object for the given
 * object, which must have two members named `validLocale' and
 * `actualLocale' of size ULOC_FULLNAME_CAPACITY
 */
#define U_LOCALE_BASED(varname, objname) \
  LocaleBased varname((objname).validLocale, (objname).actualLocale)

U_NAMESPACE_BEGIN

/**
 * A utility class that unifies the implementation of getLocale() by
 * various ICU services.  This class is likely to be removed in the
 * ICU 3.0 time frame in favor of an integrated approach with the
 * services framework.
 * @since ICU 2.8
 */
class U_COMMON_API LocaleBased : public UMemory {

 public:

    /**
     * Construct a LocaleBased wrapper around the two pointers.  These
     * will be aliased for the lifetime of this object.
     */
    inline LocaleBased(char* validAlias, char* actualAlias);

    /**
     * Construct a LocaleBased wrapper around the two const pointers.
     * These will be aliased for the lifetime of this object.
     */
    inline LocaleBased(const char* validAlias, const char* actualAlias);

    /**
     * Return locale meta-data for the service object wrapped by this
     * object.  Either the valid or the actual locale may be
     * retrieved.
     * @param type either ULOC_VALID_LOCALE or ULOC_ACTUAL_LOCALE
     * @param status input-output error code
     * @return the indicated locale
     */
    Locale getLocale(ULocDataLocaleType type, UErrorCode& status) const;

    /**
     * Return the locale ID for the service object wrapped by this
     * object.  Either the valid or the actual locale may be
     * retrieved.
     * @param type either ULOC_VALID_LOCALE or ULOC_ACTUAL_LOCALE
     * @param status input-output error code
     * @return the indicated locale ID
     */
    const char* getLocaleID(ULocDataLocaleType type, UErrorCode& status) const;

    /**
     * Set the locale meta-data for the service object wrapped by this
     * object.  If either parameter is zero, it is ignored.
     * @param valid the ID of the valid locale
     * @param actual the ID of the actual locale
     */
    void setLocaleIDs(const char* valid, const char* actual);

    /**
     * Set the locale meta-data for the service object wrapped by this
     * object.
     * @param valid the ID of the valid locale
     * @param actual the ID of the actual locale
     */
    void setLocaleIDs(const Locale& valid, const Locale& actual);

 private:

    char* valid;
    
    char* actual;
};

inline LocaleBased::LocaleBased(char* validAlias, char* actualAlias) :
    valid(validAlias), actual(actualAlias) {
}

inline LocaleBased::LocaleBased(const char* validAlias,
                                const char* actualAlias) :
    // ugh: cast away const
    valid((char*)validAlias), actual((char*)actualAlias) {
}

U_NAMESPACE_END

#endif
