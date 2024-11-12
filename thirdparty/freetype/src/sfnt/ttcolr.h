/**************************************************************************/
/*  ttcolr.h                                                              */
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
 * ttcolr.h
 *
 *   TrueType and OpenType colored glyph layer support (specification).
 *
 * Copyright (C) 2018-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * Originally written by Shao Yu Zhang <shaozhang@fb.com>.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef __TTCOLR_H__
#define __TTCOLR_H__


#include "ttload.h"


FT_BEGIN_HEADER


  FT_LOCAL( FT_Error )
  tt_face_load_colr( TT_Face    face,
                     FT_Stream  stream );

  FT_LOCAL( void )
  tt_face_free_colr( TT_Face  face );

  FT_LOCAL( FT_Bool )
  tt_face_get_colr_layer( TT_Face            face,
                          FT_UInt            base_glyph,
                          FT_UInt           *aglyph_index,
                          FT_UInt           *acolor_index,
                          FT_LayerIterator*  iterator );

  FT_LOCAL( FT_Bool )
  tt_face_get_colr_glyph_paint( TT_Face                  face,
                                FT_UInt                  base_glyph,
                                FT_Color_Root_Transform  root_transform,
                                FT_OpaquePaint*          paint );

  FT_LOCAL( FT_Bool )
  tt_face_get_color_glyph_clipbox( TT_Face      face,
                                   FT_UInt      base_glyph,
                                   FT_ClipBox*  clip_box );

  FT_LOCAL( FT_Bool )
  tt_face_get_paint_layers( TT_Face            face,
                            FT_LayerIterator*  iterator,
                            FT_OpaquePaint*    paint );

  FT_LOCAL( FT_Bool )
  tt_face_get_colorline_stops( TT_Face                face,
                               FT_ColorStop*          color_stop,
                               FT_ColorStopIterator*  iterator );

  FT_LOCAL( FT_Bool )
  tt_face_get_paint( TT_Face         face,
                     FT_OpaquePaint  opaque_paint,
                     FT_COLR_Paint*  paint );

  FT_LOCAL( FT_Error )
  tt_face_colr_blend_layer( TT_Face       face,
                            FT_UInt       color_index,
                            FT_GlyphSlot  dstSlot,
                            FT_GlyphSlot  srcSlot );


FT_END_HEADER


#endif /* __TTCOLR_H__ */

/* END */
