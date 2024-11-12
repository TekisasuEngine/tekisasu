/**************************************************************************/
/*  gxvfeat.h                                                             */
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
 * gxvfeat.h
 *
 *   TrueTypeGX/AAT feat table validation (specification).
 *
 * Copyright (C) 2004-2023 by
 * suzuki toshiya, Masatake YAMATO, Red Hat K.K.,
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

/****************************************************************************
 *
 * gxvalid is derived from both gxlayout module and otvalid module.
 * Development of gxlayout is supported by the Information-technology
 * Promotion Agency(IPA), Japan.
 *
 */


#ifndef GXVFEAT_H_
#define GXVFEAT_H_


#include "gxvalid.h"
#include "gxvcommn.h"


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                Registry predefined by Apple                   *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  /* TODO: More compact format */
  typedef struct  GXV_Feature_RegistryRec_
  {
    FT_Bool  existence;
    FT_Bool  apple_reserved;
    FT_Bool  exclusive;
    FT_Byte  nSettings;

  } GX_Feature_RegistryRec;


#define gxv_feat_registry_length                  \
          ( sizeof ( gxv_feat_registry ) /        \
              sizeof ( GX_Feature_RegistryRec ) )


  static GX_Feature_RegistryRec  gxv_feat_registry[] =
  {
    /* Generated from gxvfgen.c */
    {1, 0, 0,  1},   /* All Typographic Features */
    {1, 0, 0,  8},   /* Ligatures */
    {1, 0, 1,  3},   /* Cursive Connection */
    {1, 0, 1,  6},   /* Letter Case */
    {1, 0, 0,  1},   /* Vertical Substitution */
    {1, 0, 0,  1},   /* Linguistic Rearrangement */
    {1, 0, 1,  2},   /* Number Spacing */
    {1, 1, 0,  0},   /* Apple Reserved 1 */
    {1, 0, 0,  5},   /* Smart Swashes */
    {1, 0, 1,  3},   /* Diacritics */
    {1, 0, 1,  4},   /* Vertical Position */
    {1, 0, 1,  3},   /* Fractions */
    {1, 1, 0,  0},   /* Apple Reserved 2 */
    {1, 0, 0,  1},   /* Overlapping Characters */
    {1, 0, 0,  6},   /* Typographic Extras */
    {1, 0, 0,  5},   /* Mathematical Extras */
    {1, 0, 1,  7},   /* Ornament Sets */
    {1, 0, 1,  1},   /* Character Alternatives */
    {1, 0, 1,  5},   /* Design Complexity */
    {1, 0, 1,  6},   /* Style Options */
    {1, 0, 1, 11},   /* Character Shape */
    {1, 0, 1,  2},   /* Number Case */
    {1, 0, 1,  4},   /* Text Spacing */
    {1, 0, 1, 10},   /* Transliteration */
    {1, 0, 1,  9},   /* Annotation */
    {1, 0, 1,  2},   /* Kana Spacing */
    {1, 0, 1,  2},   /* Ideographic Spacing */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {0, 0, 0,  0},   /* __EMPTY__ */
    {1, 0, 1,  4},   /* Text Spacing */
    {1, 0, 1,  2},   /* Kana Spacing */
    {1, 0, 1,  2},   /* Ideographic Spacing */
    {1, 0, 1,  4},   /* CJK Roman Spacing */
  };


#endif /* GXVFEAT_H_ */


/* END */
