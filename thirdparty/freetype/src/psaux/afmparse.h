/**************************************************************************/
/*  afmparse.h                                                            */
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
 * afmparse.h
 *
 *   AFM parser (specification).
 *
 * Copyright (C) 2006-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef AFMPARSE_H_
#define AFMPARSE_H_


#include <freetype/internal/psaux.h>


FT_BEGIN_HEADER


  FT_LOCAL( FT_Error )
  afm_parser_init( AFM_Parser  parser,
                   FT_Memory   memory,
                   FT_Byte*    base,
                   FT_Byte*    limit );


  FT_LOCAL( void )
  afm_parser_done( AFM_Parser  parser );


  FT_LOCAL( FT_Error )
  afm_parser_parse( AFM_Parser  parser );


  enum  AFM_ValueType_
  {
    AFM_VALUE_TYPE_STRING,
    AFM_VALUE_TYPE_NAME,
    AFM_VALUE_TYPE_FIXED,   /* real number */
    AFM_VALUE_TYPE_INTEGER,
    AFM_VALUE_TYPE_BOOL,
    AFM_VALUE_TYPE_INDEX    /* glyph index */
  };


  typedef struct  AFM_ValueRec_
  {
    enum AFM_ValueType_  type;
    union
    {
      char*     s;
      FT_Fixed  f;
      FT_Int    i;
      FT_UInt   u;
      FT_Bool   b;

    } u;

  } AFM_ValueRec, *AFM_Value;

#define  AFM_MAX_ARGUMENTS  5

  FT_LOCAL( FT_Int )
  afm_parser_read_vals( AFM_Parser  parser,
                        AFM_Value   vals,
                        FT_Int      n );

  /* read the next key from the next line or column */
  FT_LOCAL( char* )
  afm_parser_next_key( AFM_Parser  parser,
                       FT_Bool     line,
                       FT_Offset*  len );

FT_END_HEADER

#endif /* AFMPARSE_H_ */


/* END */
