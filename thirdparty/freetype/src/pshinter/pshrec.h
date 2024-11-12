/**************************************************************************/
/*  pshrec.h                                                              */
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
 * pshrec.h
 *
 *   Postscript (Type1/Type2) hints recorder (specification).
 *
 * Copyright (C) 2001-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


  /***************************************************************************
   *
   * The functions defined here are called from the Type 1, CID and CFF
   * font drivers to record the hints of a given character/glyph.
   *
   * The hints are recorded in a unified format, and are later processed
   * by the `optimizer' and `fitter' to adjust the outlines to the pixel
   * grid.
   *
   */


#ifndef PSHREC_H_
#define PSHREC_H_


#include <freetype/internal/pshints.h>
#include "pshglob.h"


FT_BEGIN_HEADER


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                 GLYPH HINTS RECORDER INTERNALS                *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  /* handle to hint record */
  typedef struct PS_HintRec_*  PS_Hint;

  /* hint types */
  typedef enum  PS_Hint_Type_
  {
    PS_HINT_TYPE_1 = 1,
    PS_HINT_TYPE_2 = 2

  } PS_Hint_Type;


  /* hint flags */
#define PS_HINT_FLAG_GHOST   1U
#define PS_HINT_FLAG_BOTTOM  2U


  /* hint descriptor */
  typedef struct  PS_HintRec_
  {
    FT_Int   pos;
    FT_Int   len;
    FT_UInt  flags;

  } PS_HintRec;


#define ps_hint_is_active( x )  ( (x)->flags & PS_HINT_FLAG_ACTIVE )
#define ps_hint_is_ghost( x )   ( (x)->flags & PS_HINT_FLAG_GHOST  )
#define ps_hint_is_bottom( x )  ( (x)->flags & PS_HINT_FLAG_BOTTOM )


  /* hints table descriptor */
  typedef struct  PS_Hint_TableRec_
  {
    FT_UInt  num_hints;
    FT_UInt  max_hints;
    PS_Hint  hints;

  } PS_Hint_TableRec, *PS_Hint_Table;


  /* hint and counter mask descriptor */
  typedef struct  PS_MaskRec_
  {
    FT_UInt   num_bits;
    FT_UInt   max_bits;
    FT_Byte*  bytes;
    FT_UInt   end_point;

  } PS_MaskRec, *PS_Mask;


  /* masks and counters table descriptor */
  typedef struct  PS_Mask_TableRec_
  {
    FT_UInt  num_masks;
    FT_UInt  max_masks;
    PS_Mask  masks;

  } PS_Mask_TableRec, *PS_Mask_Table;


 /* dimension-specific hints descriptor */
  typedef struct  PS_DimensionRec_
  {
    PS_Hint_TableRec  hints;
    PS_Mask_TableRec  masks;
    PS_Mask_TableRec  counters;

  } PS_DimensionRec, *PS_Dimension;


  /* glyph hints descriptor                                */
  /* dimension 0 => X coordinates + vertical hints/stems   */
  /* dimension 1 => Y coordinates + horizontal hints/stems */
  typedef struct  PS_HintsRec_
  {
    FT_Memory        memory;
    FT_Error         error;
    FT_UInt32        magic;
    PS_Hint_Type     hint_type;
    PS_DimensionRec  dimension[2];

  } PS_HintsRec, *PS_Hints;

  /* */

  /* initialize hints recorder */
  FT_LOCAL( void )
  ps_hints_init( PS_Hints   hints,
                 FT_Memory  memory );

  /* finalize hints recorder */
  FT_LOCAL( void )
  ps_hints_done( PS_Hints  hints );

  /* initialize Type1 hints recorder interface */
  FT_LOCAL( void )
  t1_hints_funcs_init( T1_Hints_FuncsRec*  funcs );

  /* initialize Type2 hints recorder interface */
  FT_LOCAL( void )
  t2_hints_funcs_init( T2_Hints_FuncsRec*  funcs );


#ifdef DEBUG_HINTER
  extern PS_Hints  ps_debug_hints;
  extern  int      ps_debug_no_horz_hints;
  extern  int      ps_debug_no_vert_hints;
#endif

 /* */


FT_END_HEADER


#endif /* PSHREC_H_ */


/* END */
