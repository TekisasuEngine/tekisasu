/**************************************************************************/
/*  afloader.h                                                            */
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
 * afloader.h
 *
 *   Auto-fitter glyph loading routines (specification).
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


#ifndef AFLOADER_H_
#define AFLOADER_H_

#include "afhints.h"
#include "afmodule.h"
#include "afglobal.h"


FT_BEGIN_HEADER

  /*
   * The autofitter module's (global) data structure to communicate with
   * actual fonts.  If necessary, `local' data like the current face, the
   * current face's auto-hint data, or the current glyph's parameters
   * relevant to auto-hinting are `swapped in'.  Cf. functions like
   * `af_loader_reset' and `af_loader_load_g'.
   */

  typedef struct  AF_LoaderRec_
  {
    /* current face data */
    FT_Face           face;
    AF_FaceGlobals    globals;

    /* current glyph data */
    AF_GlyphHints     hints;
    AF_StyleMetrics   metrics;
    FT_Bool           transformed;
    FT_Matrix         trans_matrix;
    FT_Vector         trans_delta;
    FT_Vector         pp1;
    FT_Vector         pp2;
    /* we don't handle vertical phantom points */

  } AF_LoaderRec, *AF_Loader;


  FT_LOCAL( void )
  af_loader_init( AF_Loader      loader,
                  AF_GlyphHints  hints );


  FT_LOCAL( FT_Error )
  af_loader_reset( AF_Loader  loader,
                   AF_Module  module,
                   FT_Face    face );


  FT_LOCAL( void )
  af_loader_done( AF_Loader  loader );


  FT_LOCAL( FT_Error )
  af_loader_load_glyph( AF_Loader  loader,
                        AF_Module  module,
                        FT_Face    face,
                        FT_UInt    gindex,
                        FT_Int32   load_flags );

  FT_LOCAL( FT_Fixed )
  af_loader_compute_darkening( AF_Loader  loader,
                               FT_Face    face,
                               FT_Pos     standard_width );

/* */


FT_END_HEADER

#endif /* AFLOADER_H_ */


/* END */
