/**************************************************************************/
/*  afcjk.h                                                               */
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
 * afcjk.h
 *
 *   Auto-fitter hinting routines for CJK writing system (specification).
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


#ifndef AFCJK_H_
#define AFCJK_H_

#include "afhints.h"
#include "aflatin.h"


FT_BEGIN_HEADER


  /* the CJK-specific writing system */

  AF_DECLARE_WRITING_SYSTEM_CLASS( af_cjk_writing_system_class )


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****              C J K   G L O B A L   M E T R I C S              *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/


  /*
   * CJK glyphs tend to fill the square.  So we have both vertical and
   * horizontal blue zones.  But some glyphs have flat bounding strokes that
   * leave some space between neighbour glyphs.
   */

#define AF_CJK_IS_TOP_BLUE( b ) \
          ( (b)->properties & AF_BLUE_PROPERTY_CJK_TOP )
#define AF_CJK_IS_HORIZ_BLUE( b ) \
          ( (b)->properties & AF_BLUE_PROPERTY_CJK_HORIZ )
#define AF_CJK_IS_RIGHT_BLUE  AF_CJK_IS_TOP_BLUE

#define AF_CJK_MAX_WIDTHS  16


#define AF_CJK_BLUE_ACTIVE      ( 1U << 0 ) /* zone height is <= 3/4px      */
#define AF_CJK_BLUE_TOP         ( 1U << 1 ) /* result of AF_CJK_IS_TOP_BLUE */
#define AF_CJK_BLUE_ADJUSTMENT  ( 1U << 2 ) /* used for scale adjustment    */
                                            /* optimization                 */


  typedef struct  AF_CJKBlueRec_
  {
    AF_WidthRec  ref;
    AF_WidthRec  shoot; /* undershoot */
    FT_UInt      flags;

  } AF_CJKBlueRec, *AF_CJKBlue;


  typedef struct  AF_CJKAxisRec_
  {
    FT_Fixed       scale;
    FT_Pos         delta;

    FT_UInt        width_count;                   /* number of used widths */
    AF_WidthRec    widths[AF_CJK_MAX_WIDTHS];     /* widths array          */
    FT_Pos         edge_distance_threshold;     /* used for creating edges */
    FT_Pos         standard_width;           /* the default stem thickness */
    FT_Bool        extra_light;           /* is standard width very light? */

    /* used for horizontal metrics too for CJK */
    FT_Bool        control_overshoot;
    FT_UInt        blue_count;
    AF_CJKBlueRec  blues[AF_BLUE_STRINGSET_MAX];

    FT_Fixed       org_scale;
    FT_Pos         org_delta;

  } AF_CJKAxisRec, *AF_CJKAxis;


  typedef struct  AF_CJKMetricsRec_
  {
    AF_StyleMetricsRec  root;
    FT_UInt             units_per_em;
    AF_CJKAxisRec       axis[AF_DIMENSION_MAX];

  } AF_CJKMetricsRec, *AF_CJKMetrics;


#ifdef AF_CONFIG_OPTION_CJK
  FT_LOCAL( FT_Error )
  af_cjk_metrics_init( AF_StyleMetrics  metrics,
                       FT_Face          face );

  FT_LOCAL( void )
  af_cjk_metrics_scale( AF_StyleMetrics  metrics,
                        AF_Scaler        scaler );

  FT_LOCAL( FT_Error )
  af_cjk_hints_init( AF_GlyphHints    hints,
                     AF_StyleMetrics  metrics );

  FT_LOCAL( FT_Error )
  af_cjk_hints_apply( FT_UInt          glyph_index,
                      AF_GlyphHints    hints,
                      FT_Outline*      outline,
                      AF_StyleMetrics  metrics );

  /* shared; called from afindic.c */
  FT_LOCAL( void )
  af_cjk_metrics_check_digits( AF_CJKMetrics  metrics,
                               FT_Face        face );

  FT_LOCAL( void )
  af_cjk_metrics_init_widths( AF_CJKMetrics  metrics,
                              FT_Face        face );
#endif /* AF_CONFIG_OPTION_CJK */


/* */

FT_END_HEADER

#endif /* AFCJK_H_ */


/* END */
