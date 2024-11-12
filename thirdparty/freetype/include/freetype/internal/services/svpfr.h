/**************************************************************************/
/*  svpfr.h                                                               */
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
 * svpfr.h
 *
 *   Internal PFR service functions (specification).
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


#ifndef SVPFR_H_
#define SVPFR_H_

#include <freetype/ftpfr.h>
#include <freetype/internal/ftserv.h>


FT_BEGIN_HEADER


#define FT_SERVICE_ID_PFR_METRICS  "pfr-metrics"


  typedef FT_Error
  (*FT_PFR_GetMetricsFunc)( FT_Face    face,
                            FT_UInt   *aoutline,
                            FT_UInt   *ametrics,
                            FT_Fixed  *ax_scale,
                            FT_Fixed  *ay_scale );

  typedef FT_Error
  (*FT_PFR_GetKerningFunc)( FT_Face     face,
                            FT_UInt     left,
                            FT_UInt     right,
                            FT_Vector  *avector );

  typedef FT_Error
  (*FT_PFR_GetAdvanceFunc)( FT_Face   face,
                            FT_UInt   gindex,
                            FT_Pos   *aadvance );


  FT_DEFINE_SERVICE( PfrMetrics )
  {
    FT_PFR_GetMetricsFunc  get_metrics;
    FT_PFR_GetKerningFunc  get_kerning;
    FT_PFR_GetAdvanceFunc  get_advance;

  };


FT_END_HEADER

#endif /* SVPFR_H_ */


/* END */
