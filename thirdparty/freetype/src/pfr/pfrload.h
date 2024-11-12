/**************************************************************************/
/*  pfrload.h                                                             */
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
 * pfrload.h
 *
 *   FreeType PFR loader (specification).
 *
 * Copyright (C) 2002-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef PFRLOAD_H_
#define PFRLOAD_H_

#include "pfrobjs.h"
#include <freetype/internal/ftstream.h>


FT_BEGIN_HEADER

  /* some size checks should be always done (mainly to prevent */
  /* excessive allocation for malformed data), ...             */
#define PFR_CHECK_SIZE( x )  do                       \
                             {                        \
                               if ( p + (x) > limit ) \
                                 goto Too_Short;      \
                             } while ( 0 )

  /* ... and some only if intensive checking is explicitly requested */
#ifdef PFR_CONFIG_NO_CHECKS
#define PFR_CHECK( x )  do { } while ( 0 )
#else
#define PFR_CHECK  PFR_CHECK_SIZE
#endif

#define PFR_NEXT_BYTE( p )    FT_NEXT_BYTE( p )
#define PFR_NEXT_INT8( p )    FT_NEXT_CHAR( p )
#define PFR_NEXT_SHORT( p )   FT_NEXT_SHORT( p )
#define PFR_NEXT_USHORT( p )  FT_NEXT_USHORT( p )
#define PFR_NEXT_LONG( p )    FT_NEXT_OFF3( p )
#define PFR_NEXT_ULONG( p )   FT_NEXT_UOFF3( p )


 /* handling extra items */

  typedef FT_Error
  (*PFR_ExtraItem_ParseFunc)( FT_Byte*    p,
                              FT_Byte*    limit,
                              FT_Pointer  data );

  typedef struct  PFR_ExtraItemRec_
  {
    FT_UInt                  type;
    PFR_ExtraItem_ParseFunc  parser;

  } PFR_ExtraItemRec;

  typedef const struct PFR_ExtraItemRec_*  PFR_ExtraItem;


  FT_LOCAL( FT_Error )
  pfr_extra_items_skip( FT_Byte*  *pp,
                        FT_Byte*  limit );

  FT_LOCAL( FT_Error )
  pfr_extra_items_parse( FT_Byte*      *pp,
                         FT_Byte*       limit,
                         PFR_ExtraItem  item_list,
                         FT_Pointer     item_data );


  /* load a PFR header */
  FT_LOCAL( FT_Error )
  pfr_header_load( PFR_Header  header,
                   FT_Stream   stream );

  /* check a PFR header */
  FT_LOCAL( FT_Bool )
  pfr_header_check( PFR_Header  header );


  /* return number of logical fonts in this file */
  FT_LOCAL( FT_Error )
  pfr_log_font_count( FT_Stream   stream,
                      FT_UInt32   log_section_offset,
                      FT_Long    *acount );

  /* load a pfr logical font entry */
  FT_LOCAL( FT_Error )
  pfr_log_font_load( PFR_LogFont  log_font,
                     FT_Stream    stream,
                     FT_UInt      face_index,
                     FT_UInt32    section_offset,
                     FT_Bool      size_increment );


  /* load a physical font entry */
  FT_LOCAL( FT_Error )
  pfr_phy_font_load( PFR_PhyFont  phy_font,
                     FT_Stream    stream,
                     FT_UInt32    offset,
                     FT_UInt32    size );

  /* finalize a physical font */
  FT_LOCAL( void )
  pfr_phy_font_done( PFR_PhyFont  phy_font,
                     FT_Memory    memory );

  /* */

FT_END_HEADER

#endif /* PFRLOAD_H_ */


/* END */
