/**************************************************************************/
/*  ftmisc.h                                                              */
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
 * ftmisc.h
 *
 *   Miscellaneous macros for stand-alone rasterizer (specification
 *   only).
 *
 * Copyright (C) 2005-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used
 * modified and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


  /****************************************************
   *
   * This file is *not* portable!  You have to adapt
   * its definitions to your platform.
   *
   */

#ifndef FTMISC_H_
#define FTMISC_H_


  /* memset */
#include FT_CONFIG_STANDARD_LIBRARY_H

#define FT_BEGIN_HEADER
#define FT_END_HEADER

#define FT_LOCAL_DEF( x )   static x


  /* from include/freetype/fttypes.h */

  typedef unsigned char  FT_Byte;
  typedef signed int     FT_Int;
  typedef unsigned int   FT_UInt;
  typedef signed long    FT_Long;
  typedef unsigned long  FT_ULong;
  typedef signed long    FT_F26Dot6;
  typedef int            FT_Error;


#define FT_STATIC_BYTE_CAST( type, var )  (type)(FT_Byte)(var)


  /* from include/freetype/ftsystem.h */

  typedef struct FT_MemoryRec_*  FT_Memory;

  typedef void* (*FT_Alloc_Func)( FT_Memory  memory,
                                  long       size );

  typedef void (*FT_Free_Func)( FT_Memory  memory,
                                void*      block );

  typedef void* (*FT_Realloc_Func)( FT_Memory  memory,
                                    long       cur_size,
                                    long       new_size,
                                    void*      block );

  typedef struct FT_MemoryRec_
  {
    void*            user;

    FT_Alloc_Func    alloc;
    FT_Free_Func     free;
    FT_Realloc_Func  realloc;

  } FT_MemoryRec;


  /* from src/ftcalc.c */

#if ( defined _WIN32 || defined _WIN64 )

  typedef __int64  FT_Int64;

#else

#include "inttypes.h"

  typedef int64_t  FT_Int64;

#endif


  static FT_Long
  FT_MulDiv( FT_Long  a,
             FT_Long  b,
             FT_Long  c )
  {
    FT_Int   s;
    FT_Long  d;


    s = 1;
    if ( a < 0 ) { a = -a; s = -1; }
    if ( b < 0 ) { b = -b; s = -s; }
    if ( c < 0 ) { c = -c; s = -s; }

    d = (FT_Long)( c > 0 ? ( (FT_Int64)a * b + ( c >> 1 ) ) / c
                         : 0x7FFFFFFFL );

    return ( s > 0 ) ? d : -d;
  }


  static FT_Long
  FT_MulDiv_No_Round( FT_Long  a,
                      FT_Long  b,
                      FT_Long  c )
  {
    FT_Int   s;
    FT_Long  d;


    s = 1;
    if ( a < 0 ) { a = -a; s = -1; }
    if ( b < 0 ) { b = -b; s = -s; }
    if ( c < 0 ) { c = -c; s = -s; }

    d = (FT_Long)( c > 0 ? (FT_Int64)a * b / c
                         : 0x7FFFFFFFL );

    return ( s > 0 ) ? d : -d;
  }

#endif /* FTMISC_H_ */


/* END */
