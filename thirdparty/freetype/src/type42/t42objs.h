/**************************************************************************/
/*  t42objs.h                                                             */
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
 * t42objs.h
 *
 *   Type 42 objects manager (specification).
 *
 * Copyright (C) 2002-2023 by
 * Roberto Alameda.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef T42OBJS_H_
#define T42OBJS_H_

#include <freetype/freetype.h>
#include <freetype/t1tables.h>
#include <freetype/internal/t1types.h>
#include "t42types.h"
#include <freetype/internal/ftobjs.h>
#include <freetype/internal/ftdrv.h>
#include <freetype/internal/services/svpscmap.h>
#include <freetype/internal/pshints.h>


FT_BEGIN_HEADER


  /* Type42 size */
  typedef struct  T42_SizeRec_
  {
    FT_SizeRec  root;
    FT_Size     ttsize;

  } T42_SizeRec, *T42_Size;


  /* Type42 slot */
  typedef struct  T42_GlyphSlotRec_
  {
    FT_GlyphSlotRec  root;
    FT_GlyphSlot     ttslot;

  } T42_GlyphSlotRec, *T42_GlyphSlot;


  /* Type 42 driver */
  typedef struct  T42_DriverRec_
  {
    FT_DriverRec     root;
    FT_Driver_Class  ttclazz;

  } T42_DriverRec, *T42_Driver;


  /* */


  FT_LOCAL( FT_Error )
  T42_Face_Init( FT_Stream      stream,
                 FT_Face        face,
                 FT_Int         face_index,
                 FT_Int         num_params,
                 FT_Parameter*  params );


  FT_LOCAL( void )
  T42_Face_Done( FT_Face  face );


  FT_LOCAL( FT_Error )
  T42_Size_Init( FT_Size  size );


  FT_LOCAL( FT_Error )
  T42_Size_Request( FT_Size          size,
                    FT_Size_Request  req );


  FT_LOCAL( FT_Error )
  T42_Size_Select( FT_Size   size,
                   FT_ULong  strike_index );


  FT_LOCAL( void )
  T42_Size_Done( FT_Size  size );


  FT_LOCAL( FT_Error )
  T42_GlyphSlot_Init( FT_GlyphSlot  slot );


  FT_LOCAL( FT_Error )
  T42_GlyphSlot_Load( FT_GlyphSlot  glyph,
                      FT_Size       size,
                      FT_UInt       glyph_index,
                      FT_Int32      load_flags );

  FT_LOCAL( void )
  T42_GlyphSlot_Done( FT_GlyphSlot  slot );


  FT_LOCAL( FT_Error )
  T42_Driver_Init( FT_Module  module );

  FT_LOCAL( void )
  T42_Driver_Done( FT_Module  module );

 /* */

FT_END_HEADER


#endif /* T42OBJS_H_ */


/* END */
