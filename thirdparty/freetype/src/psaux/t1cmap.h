/**************************************************************************/
/*  t1cmap.h                                                              */
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
 * t1cmap.h
 *
 *   Type 1 character map support (specification).
 *
 * Copyright (C) 2002-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef T1CMAP_H_
#define T1CMAP_H_

#include <freetype/internal/ftobjs.h>
#include <freetype/internal/t1types.h>

FT_BEGIN_HEADER


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****          TYPE1 STANDARD (AND EXPERT) ENCODING CMAPS           *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  /* standard (and expert) encoding cmaps */
  typedef struct T1_CMapStdRec_*  T1_CMapStd;

  typedef struct  T1_CMapStdRec_
  {
    FT_CMapRec                cmap;

    const FT_UShort*          code_to_sid;
    PS_Adobe_Std_StringsFunc  sid_to_string;

    FT_UInt                   num_glyphs;
    const char* const*        glyph_names;

  } T1_CMapStdRec;


  FT_CALLBACK_TABLE const FT_CMap_ClassRec
  t1_cmap_standard_class_rec;

  FT_CALLBACK_TABLE const FT_CMap_ClassRec
  t1_cmap_expert_class_rec;


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                  TYPE1 CUSTOM ENCODING CMAP                   *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  typedef struct T1_CMapCustomRec_*  T1_CMapCustom;

  typedef struct  T1_CMapCustomRec_
  {
    FT_CMapRec  cmap;
    FT_UInt     first;
    FT_UInt     count;
    FT_UShort*  indices;

  } T1_CMapCustomRec;


  FT_CALLBACK_TABLE const FT_CMap_ClassRec
  t1_cmap_custom_class_rec;


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****             TYPE1 SYNTHETIC UNICODE ENCODING CMAP             *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  /* unicode (synthetic) cmaps */

  FT_CALLBACK_TABLE const FT_CMap_ClassRec
  t1_cmap_unicode_class_rec;

 /* */


FT_END_HEADER

#endif /* T1CMAP_H_ */


/* END */
