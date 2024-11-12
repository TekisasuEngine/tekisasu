/**************************************************************************/
/*  cidgload.h                                                            */
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
 * cidgload.h
 *
 *   OpenType Glyph Loader (specification).
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


#ifndef CIDGLOAD_H_
#define CIDGLOAD_H_


#include "cidobjs.h"


FT_BEGIN_HEADER


#if 0

  /* Compute the maximum advance width of a font through quick parsing */
  FT_LOCAL( FT_Error )
  cid_face_compute_max_advance( CID_Face  face,
                                FT_Int*   max_advance );

#endif /* 0 */

  FT_LOCAL( FT_Error )
  cid_slot_load_glyph( FT_GlyphSlot  glyph,         /* CID_Glyph_Slot */
                       FT_Size       size,          /* CID_Size       */
                       FT_UInt       glyph_index,
                       FT_Int32      load_flags );


  FT_LOCAL( FT_Error )
  cid_compute_fd_and_offsets( CID_Face   face,
                              FT_UInt    glyph_index,
                              FT_ULong*  fd_select_p,
                              FT_ULong*  off1_p,
                              FT_ULong*  off2_p );


FT_END_HEADER

#endif /* CIDGLOAD_H_ */


/* END */
