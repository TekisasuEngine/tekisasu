/**************************************************************************/
/*  svttcmap.h                                                            */
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
 * svttcmap.h
 *
 *   The FreeType TrueType/sfnt cmap extra information service.
 *
 * Copyright (C) 2003-2023 by
 * Masatake YAMATO, Redhat K.K.,
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

/* Development of this service is support of
   Information-technology Promotion Agency, Japan. */

#ifndef SVTTCMAP_H_
#define SVTTCMAP_H_

#include <freetype/internal/ftserv.h>
#include <freetype/tttables.h>


FT_BEGIN_HEADER


#define FT_SERVICE_ID_TT_CMAP  "tt-cmaps"


  /**************************************************************************
   *
   * @struct:
   *   TT_CMapInfo
   *
   * @description:
   *   A structure used to store TrueType/sfnt specific cmap information
   *   which is not covered by the generic @FT_CharMap structure.  This
   *   structure can be accessed with the @FT_Get_TT_CMap_Info function.
   *
   * @fields:
   *   language ::
   *     The language ID used in Mac fonts.  Definitions of values are in
   *     `ttnameid.h`.
   *
   *   format ::
   *     The cmap format.  OpenType 1.6 defines the formats 0 (byte encoding
   *     table), 2~(high-byte mapping through table), 4~(segment mapping to
   *     delta values), 6~(trimmed table mapping), 8~(mixed 16-bit and 32-bit
   *     coverage), 10~(trimmed array), 12~(segmented coverage), 13~(last
   *     resort font), and 14 (Unicode Variation Sequences).
   */
  typedef struct  TT_CMapInfo_
  {
    FT_ULong  language;
    FT_Long   format;

  } TT_CMapInfo;


  typedef FT_Error
  (*TT_CMap_Info_GetFunc)( FT_CharMap    charmap,
                           TT_CMapInfo  *cmap_info );


  FT_DEFINE_SERVICE( TTCMaps )
  {
    TT_CMap_Info_GetFunc  get_cmap_info;
  };


#define FT_DEFINE_SERVICE_TTCMAPSREC( class_, get_cmap_info_ )  \
  static const FT_Service_TTCMapsRec  class_ =                  \
  {                                                             \
    get_cmap_info_                                              \
  };

  /* */


FT_END_HEADER

#endif /* SVTTCMAP_H_ */


/* END */
