/**************************************************************************/
/*  ucln_in.h                                                             */
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
* Copyright (C) 2001-2016, International Business Machines
*                Corporation and others. All Rights Reserved.
******************************************************************************
*   file name:  ucln_in.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2001July05
*   created by: George Rhoten
*/

#ifndef __UCLN_IN_H__
#define __UCLN_IN_H__

#include "unicode/utypes.h"
#include "ucln.h"

/*
Please keep the order of enums declared in same order
as the functions are suppose to be called.
It's usually best to have child dependencies called first. */
typedef enum ECleanupI18NType {
    UCLN_I18N_START = -1,
    UCLN_I18N_UNIT_EXTRAS,
    UCLN_I18N_NUMBER_SKELETONS,
    UCLN_I18N_CURRENCY_SPACING,
    UCLN_I18N_SPOOF,
    UCLN_I18N_SPOOFDATA,
    UCLN_I18N_TRANSLITERATOR,
    UCLN_I18N_REGEX,
    UCLN_I18N_JAPANESE_CALENDAR,
    UCLN_I18N_ISLAMIC_CALENDAR,
    UCLN_I18N_CHINESE_CALENDAR,
    UCLN_I18N_HEBREW_CALENDAR,
    UCLN_I18N_ASTRO_CALENDAR,
    UCLN_I18N_DANGI_CALENDAR,
    UCLN_I18N_CALENDAR,
    UCLN_I18N_TIMEZONEFORMAT,
    UCLN_I18N_TZDBTIMEZONENAMES,
    UCLN_I18N_TIMEZONEGENERICNAMES,
    UCLN_I18N_TIMEZONENAMES,
    UCLN_I18N_ZONEMETA,
    UCLN_I18N_TIMEZONE,
    UCLN_I18N_DIGITLIST,
    UCLN_I18N_DECFMT,
    UCLN_I18N_NUMFMT,
    UCLN_I18N_ALLOWED_HOUR_FORMATS,
    UCLN_I18N_DAYPERIODRULES,
    UCLN_I18N_SMPDTFMT,
    UCLN_I18N_USEARCH,
    UCLN_I18N_COLLATOR,
    UCLN_I18N_UCOL_RES,
    UCLN_I18N_CSDET,
    UCLN_I18N_COLLATION_ROOT,
    UCLN_I18N_GENDERINFO,
    UCLN_I18N_CDFINFO,
    UCLN_I18N_REGION,
    UCLN_I18N_LIST_FORMATTER,
    UCLN_I18N_NUMSYS,
    UCLN_I18N_COUNT /* This must be last */
} ECleanupI18NType;

/* Main library cleanup registration function. */
/* See common/ucln.h for details on adding a cleanup function. */
/* Note: the global mutex must not be held when calling this function. */
U_CFUNC void U_EXPORT2 ucln_i18n_registerCleanup(ECleanupI18NType type,
                                                 cleanupFunc *func);

#endif
