/**************************************************************************/
/*  svpsinfo.h                                                            */
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
 * svpsinfo.h
 *
 *   The FreeType PostScript info service (specification).
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


#ifndef SVPSINFO_H_
#define SVPSINFO_H_

#include <freetype/internal/ftserv.h>
#include <freetype/internal/t1types.h>


FT_BEGIN_HEADER


#define FT_SERVICE_ID_POSTSCRIPT_INFO  "postscript-info"


  typedef FT_Error
  (*PS_GetFontInfoFunc)( FT_Face          face,
                         PS_FontInfoRec*  afont_info );

  typedef FT_Error
  (*PS_GetFontExtraFunc)( FT_Face           face,
                          PS_FontExtraRec*  afont_extra );

  typedef FT_Int
  (*PS_HasGlyphNamesFunc)( FT_Face  face );

  typedef FT_Error
  (*PS_GetFontPrivateFunc)( FT_Face         face,
                            PS_PrivateRec*  afont_private );

  typedef FT_Long
  (*PS_GetFontValueFunc)( FT_Face       face,
                          PS_Dict_Keys  key,
                          FT_UInt       idx,
                          void         *value,
                          FT_Long       value_len );


  FT_DEFINE_SERVICE( PsInfo )
  {
    PS_GetFontInfoFunc     ps_get_font_info;
    PS_GetFontExtraFunc    ps_get_font_extra;
    PS_HasGlyphNamesFunc   ps_has_glyph_names;
    PS_GetFontPrivateFunc  ps_get_font_private;
    PS_GetFontValueFunc    ps_get_font_value;
  };


#define FT_DEFINE_SERVICE_PSINFOREC( class_,                     \
                                     get_font_info_,             \
                                     ps_get_font_extra_,         \
                                     has_glyph_names_,           \
                                     get_font_private_,          \
                                     get_font_value_ )           \
  static const FT_Service_PsInfoRec  class_ =                    \
  {                                                              \
    get_font_info_, ps_get_font_extra_, has_glyph_names_,        \
    get_font_private_, get_font_value_                           \
  };

  /* */


FT_END_HEADER


#endif /* SVPSINFO_H_ */


/* END */
