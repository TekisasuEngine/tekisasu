/**************************************************************************/
/*  ptypes.h                                                              */
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
*
*   Copyright (C) 1997-2012, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
******************************************************************************
*
*  FILE NAME : ptypes.h
*
*   Date        Name        Description
*   05/13/98    nos         Creation (content moved here from ptypes.h).
*   03/02/99    stephen     Added AS400 support.
*   03/30/99    stephen     Added Linux support.
*   04/13/99    stephen     Reworked for autoconf.
*   09/18/08    srl         Moved basic types back to ptypes.h from platform.h
******************************************************************************
*/

/**
 * \file
 * \brief C API: Definitions of integer types of various widths
 */

#ifndef _PTYPES_H
#define _PTYPES_H

/**
 * \def __STDC_LIMIT_MACROS
 * According to the Linux stdint.h, the ISO C99 standard specifies that in C++ implementations
 * macros like INT32_MIN and UINTPTR_MAX should only be defined if explicitly requested.
 * We need to define __STDC_LIMIT_MACROS before including stdint.h in C++ code
 * that uses such limit macros.
 * @internal
 */
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

/* NULL, size_t, wchar_t */
#include <stddef.h>

/* More platform-specific definitions. */
#include "unicode/platform.h"

/*===========================================================================*/
/* Generic data types                                                        */
/*===========================================================================*/

#include <stdint.h>

// C++11 and C11 both specify that the data type char16_t should exist, C++11
// as a keyword and C11 as a typedef in the uchar.h header file, but not all
// implementations (looking at you, Apple, spring 2024) actually do this, so
// ICU4C must detect and deal with that.
#if !defined(__cplusplus) && !defined(U_IN_DOXYGEN)
#   if U_HAVE_CHAR16_T
#       include <uchar.h>
#   else
        typedef uint16_t char16_t;
#   endif
#endif

#endif /* _PTYPES_H */
