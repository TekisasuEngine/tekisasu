/**************************************************************************/
/*  t1load.h                                                              */
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
 * t1load.h
 *
 *   Type 1 font loader (specification).
 *
 * Copyright (C) 1996-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef T1LOAD_H_
#define T1LOAD_H_


#include <freetype/internal/ftstream.h>
#include <freetype/internal/psaux.h>
#include <freetype/ftmm.h>

#include "t1parse.h"


FT_BEGIN_HEADER


  typedef struct  T1_Loader_
  {
    T1_ParserRec  parser;          /* parser used to read the stream */

    FT_Int        num_chars;       /* number of characters in encoding */
    PS_TableRec   encoding_table;  /* PS_Table used to store the       */
                                   /* encoding character names         */

    FT_Int        num_glyphs;
    PS_TableRec   glyph_names;
    PS_TableRec   charstrings;
    PS_TableRec   swap_table;      /* For moving .notdef glyph to index 0. */

    FT_Int        num_subrs;
    PS_TableRec   subrs;
    FT_Hash       subrs_hash;
    FT_Bool       fontdata;

    FT_UInt       keywords_encountered; /* T1_LOADER_ENCOUNTERED_XXX */

  } T1_LoaderRec, *T1_Loader;


  /* treatment of some keywords differs depending on whether */
  /* they precede or follow certain other keywords           */

#define T1_PRIVATE                ( 1 << 0 )
#define T1_FONTDIR_AFTER_PRIVATE  ( 1 << 1 )


  FT_LOCAL( FT_Error )
  T1_Open_Face( T1_Face  face );

#ifndef T1_CONFIG_OPTION_NO_MM_SUPPORT

  FT_LOCAL( FT_Error )
  T1_Get_Multi_Master( FT_Face           face,
                       FT_Multi_Master*  master );

  FT_LOCAL( FT_Error )
  T1_Get_MM_Var( FT_Face      face,
                 FT_MM_Var*  *master );

  FT_LOCAL( FT_Error )
  T1_Set_MM_Blend( FT_Face    face,
                   FT_UInt    num_coords,
                   FT_Fixed*  coords );

  FT_LOCAL( FT_Error )
  T1_Get_MM_Blend( FT_Face    face,
                   FT_UInt    num_coords,
                   FT_Fixed*  coords );

  FT_LOCAL( FT_Error )
  T1_Set_MM_Design( FT_Face   face,
                    FT_UInt   num_coords,
                    FT_Long*  coords );

  FT_LOCAL( FT_Error )
  T1_Reset_MM_Blend( FT_Face  face,
                     FT_UInt  instance_index );

  FT_LOCAL( FT_Error )
  T1_Get_Var_Design( FT_Face    face,
                     FT_UInt    num_coords,
                     FT_Fixed*  coords );

  FT_LOCAL( FT_Error )
  T1_Set_Var_Design( FT_Face    face,
                     FT_UInt    num_coords,
                     FT_Fixed*  coords );

  FT_LOCAL( void )
  T1_Done_Blend( FT_Face  face );

  FT_LOCAL( FT_Error )
  T1_Set_MM_WeightVector( FT_Face    face,
                          FT_UInt    len,
                          FT_Fixed*  weightvector );

  FT_LOCAL( FT_Error )
  T1_Get_MM_WeightVector( FT_Face    face,
                          FT_UInt*   len,
                          FT_Fixed*  weightvector );

#endif /* !T1_CONFIG_OPTION_NO_MM_SUPPORT */


FT_END_HEADER

#endif /* T1LOAD_H_ */


/* END */
