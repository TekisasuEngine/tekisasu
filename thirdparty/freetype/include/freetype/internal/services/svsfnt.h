/**************************************************************************/
/*  svsfnt.h                                                              */
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
 * svsfnt.h
 *
 *   The FreeType SFNT table loading service (specification).
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


#ifndef SVSFNT_H_
#define SVSFNT_H_

#include <freetype/internal/ftserv.h>
#include <freetype/tttables.h>


FT_BEGIN_HEADER


  /*
   * SFNT table loading service.
   */

#define FT_SERVICE_ID_SFNT_TABLE  "sfnt-table"


  /*
   * Used to implement FT_Load_Sfnt_Table().
   */
  typedef FT_Error
  (*FT_SFNT_TableLoadFunc)( FT_Face    face,
                            FT_ULong   tag,
                            FT_Long    offset,
                            FT_Byte*   buffer,
                            FT_ULong*  length );

  /*
   * Used to implement FT_Get_Sfnt_Table().
   */
  typedef void*
  (*FT_SFNT_TableGetFunc)( FT_Face      face,
                           FT_Sfnt_Tag  tag );


  /*
   * Used to implement FT_Sfnt_Table_Info().
   */
  typedef FT_Error
  (*FT_SFNT_TableInfoFunc)( FT_Face    face,
                            FT_UInt    idx,
                            FT_ULong  *tag,
                            FT_ULong  *offset,
                            FT_ULong  *length );


  FT_DEFINE_SERVICE( SFNT_Table )
  {
    FT_SFNT_TableLoadFunc  load_table;
    FT_SFNT_TableGetFunc   get_table;
    FT_SFNT_TableInfoFunc  table_info;
  };


#define FT_DEFINE_SERVICE_SFNT_TABLEREC( class_, load_, get_, info_ )  \
  static const FT_Service_SFNT_TableRec  class_ =                      \
  {                                                                    \
    load_, get_, info_                                                 \
  };

  /* */


FT_END_HEADER


#endif /* SVSFNT_H_ */


/* END */
