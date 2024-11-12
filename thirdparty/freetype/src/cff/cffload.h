/**************************************************************************/
/*  cffload.h                                                             */
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
 * cffload.h
 *
 *   OpenType & CFF data/program tables loader (specification).
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


#ifndef CFFLOAD_H_
#define CFFLOAD_H_


#include <freetype/internal/cfftypes.h>
#include "cffparse.h"
#include <freetype/internal/cffotypes.h>  /* for CFF_Face */


FT_BEGIN_HEADER

  FT_LOCAL( FT_UShort )
  cff_get_standard_encoding( FT_UInt  charcode );


  FT_LOCAL( FT_String* )
  cff_index_get_string( CFF_Font  font,
                        FT_UInt   element );

  FT_LOCAL( FT_String* )
  cff_index_get_sid_string( CFF_Font  font,
                            FT_UInt   sid );


  FT_LOCAL( FT_Error )
  cff_index_access_element( CFF_Index  idx,
                            FT_UInt    element,
                            FT_Byte**  pbytes,
                            FT_ULong*  pbyte_len );

  FT_LOCAL( void )
  cff_index_forget_element( CFF_Index  idx,
                            FT_Byte**  pbytes );

  FT_LOCAL( FT_String* )
  cff_index_get_name( CFF_Font  font,
                      FT_UInt   element );


  FT_LOCAL( FT_UInt )
  cff_charset_cid_to_gindex( CFF_Charset  charset,
                             FT_UInt      cid );


  FT_LOCAL( FT_Error )
  cff_font_load( FT_Library  library,
                 FT_Stream   stream,
                 FT_Int      face_index,
                 CFF_Font    font,
                 CFF_Face    face,
                 FT_Bool     pure_cff,
                 FT_Bool     cff2 );

  FT_LOCAL( void )
  cff_font_done( CFF_Font  font );


  FT_LOCAL( FT_Error )
  cff_load_private_dict( CFF_Font     font,
                         CFF_SubFont  subfont,
                         FT_UInt      lenNDV,
                         FT_Fixed*    NDV );

  FT_LOCAL( FT_Byte )
  cff_fd_select_get( CFF_FDSelect  fdselect,
                     FT_UInt       glyph_index );

  FT_LOCAL( FT_Bool )
  cff_blend_check_vector( CFF_Blend  blend,
                          FT_UInt    vsindex,
                          FT_UInt    lenNDV,
                          FT_Fixed*  NDV );

  FT_LOCAL( FT_Error )
  cff_blend_build_vector( CFF_Blend  blend,
                          FT_UInt    vsindex,
                          FT_UInt    lenNDV,
                          FT_Fixed*  NDV );

  FT_LOCAL( void )
  cff_blend_clear( CFF_SubFont  subFont );

  FT_LOCAL( FT_Error )
  cff_blend_doBlend( CFF_SubFont  subfont,
                     CFF_Parser   parser,
                     FT_UInt      numBlends );

#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
  FT_LOCAL( FT_Error )
  cff_get_var_blend( FT_Face      face,
                     FT_UInt     *num_coords,
                     FT_Fixed*   *coords,
                     FT_Fixed*   *normalizedcoords,
                     FT_MM_Var*  *mm_var );

  FT_LOCAL( void )
  cff_done_blend( FT_Face  face );
#endif


FT_END_HEADER

#endif /* CFFLOAD_H_ */


/* END */
