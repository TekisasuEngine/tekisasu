/**************************************************************************/
/*  svfntfmt.h                                                            */
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

 *
 * svfntfmt.h
 *
 *   The FreeType font format service (specification only).
 *
 * Copyright (C) 2003-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef SVFNTFMT_H_
#define SVFNTFMT_H_

#include <freetype/internal/ftserv.h>


FT_BEGIN_HEADER


  /*
   * A trivial service used to return the name of a face's font driver,
   * according to the XFree86 nomenclature.  Note that the service data is a
   * simple constant string pointer.
   */

#define FT_SERVICE_ID_FONT_FORMAT  "font-format"

#define FT_FONT_FORMAT_TRUETYPE  "TrueType"
#define FT_FONT_FORMAT_TYPE_1    "Type 1"
#define FT_FONT_FORMAT_BDF       "BDF"
#define FT_FONT_FORMAT_PCF       "PCF"
#define FT_FONT_FORMAT_TYPE_42   "Type 42"
#define FT_FONT_FORMAT_CID       "CID Type 1"
#define FT_FONT_FORMAT_CFF       "CFF"
#define FT_FONT_FORMAT_PFR       "PFR"
#define FT_FONT_FORMAT_WINFNT    "Windows FNT"

  /* */


FT_END_HEADER


#endif /* SVFNTFMT_H_ */


/* END */
