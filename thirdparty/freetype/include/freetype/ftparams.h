/**************************************************************************/
/*  ftparams.h                                                            */
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
 * ftparams.h
 *
 *   FreeType API for possible FT_Parameter tags (specification only).
 *
 * Copyright (C) 2017-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef FTPARAMS_H_
#define FTPARAMS_H_

#include <freetype/freetype.h>

#ifdef FREETYPE_H
#error "freetype.h of FreeType 1 has been loaded!"
#error "Please fix the directory search order for header files"
#error "so that freetype.h of FreeType 2 is found first."
#endif


FT_BEGIN_HEADER


  /**************************************************************************
   *
   * @section:
   *   parameter_tags
   *
   * @title:
   *   Parameter Tags
   *
   * @abstract:
   *   Macros for driver property and font loading parameter tags.
   *
   * @description:
   *   This section contains macros for the @FT_Parameter structure that are
   *   used with various functions to activate some special functionality or
   *   different behaviour of various components of FreeType.
   *
   */


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_FAMILY
   *
   * @description:
   *   A tag for @FT_Parameter to make @FT_Open_Face ignore typographic
   *   family names in the 'name' table (introduced in OpenType version 1.4).
   *   Use this for backward compatibility with legacy systems that have a
   *   four-faces-per-family restriction.
   *
   * @since:
   *   2.8
   *
   */
#define FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_FAMILY \
          FT_MAKE_TAG( 'i', 'g', 'p', 'f' )


  /* this constant is deprecated */
#define FT_PARAM_TAG_IGNORE_PREFERRED_FAMILY \
          FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_FAMILY


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_SUBFAMILY
   *
   * @description:
   *   A tag for @FT_Parameter to make @FT_Open_Face ignore typographic
   *   subfamily names in the 'name' table (introduced in OpenType version
   *   1.4).  Use this for backward compatibility with legacy systems that
   *   have a four-faces-per-family restriction.
   *
   * @since:
   *   2.8
   *
   */
#define FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_SUBFAMILY \
          FT_MAKE_TAG( 'i', 'g', 'p', 's' )


  /* this constant is deprecated */
#define FT_PARAM_TAG_IGNORE_PREFERRED_SUBFAMILY \
          FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_SUBFAMILY


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_INCREMENTAL
   *
   * @description:
   *   An @FT_Parameter tag to be used with @FT_Open_Face to indicate
   *   incremental glyph loading.
   *
   */
#define FT_PARAM_TAG_INCREMENTAL \
          FT_MAKE_TAG( 'i', 'n', 'c', 'r' )


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_IGNORE_SBIX
   *
   * @description:
   *   A tag for @FT_Parameter to make @FT_Open_Face ignore an 'sbix' table
   *   while loading a font.  Use this if @FT_FACE_FLAG_SBIX is set and you
   *   want to access the outline glyphs in the font.
   *
   */
#define FT_PARAM_TAG_IGNORE_SBIX \
          FT_MAKE_TAG( 'i', 's', 'b', 'x' )


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_LCD_FILTER_WEIGHTS
   *
   * @description:
   *   An @FT_Parameter tag to be used with @FT_Face_Properties.  The
   *   corresponding argument specifies the five LCD filter weights for a
   *   given face (if using @FT_LOAD_TARGET_LCD, for example), overriding the
   *   global default values or the values set up with
   *   @FT_Library_SetLcdFilterWeights.
   *
   * @since:
   *   2.8
   *
   */
#define FT_PARAM_TAG_LCD_FILTER_WEIGHTS \
          FT_MAKE_TAG( 'l', 'c', 'd', 'f' )


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_RANDOM_SEED
   *
   * @description:
   *   An @FT_Parameter tag to be used with @FT_Face_Properties.  The
   *   corresponding 32bit signed integer argument overrides the font
   *   driver's random seed value with a face-specific one; see @random-seed.
   *
   * @since:
   *   2.8
   *
   */
#define FT_PARAM_TAG_RANDOM_SEED \
          FT_MAKE_TAG( 's', 'e', 'e', 'd' )


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_STEM_DARKENING
   *
   * @description:
   *   An @FT_Parameter tag to be used with @FT_Face_Properties.  The
   *   corresponding Boolean argument specifies whether to apply stem
   *   darkening, overriding the global default values or the values set up
   *   with @FT_Property_Set (see @no-stem-darkening).
   *
   *   This is a passive setting that only takes effect if the font driver or
   *   autohinter honors it, which the CFF, Type~1, and CID drivers always
   *   do, but the autohinter only in 'light' hinting mode (as of version
   *   2.9).
   *
   * @since:
   *   2.8
   *
   */
#define FT_PARAM_TAG_STEM_DARKENING \
          FT_MAKE_TAG( 'd', 'a', 'r', 'k' )


  /**************************************************************************
   *
   * @enum:
   *   FT_PARAM_TAG_UNPATENTED_HINTING
   *
   * @description:
   *   Deprecated, no effect.
   *
   *   Previously: A constant used as the tag of an @FT_Parameter structure
   *   to indicate that unpatented methods only should be used by the
   *   TrueType bytecode interpreter for a typeface opened by @FT_Open_Face.
   *
   */
#define FT_PARAM_TAG_UNPATENTED_HINTING \
          FT_MAKE_TAG( 'u', 'n', 'p', 'a' )


  /* */


FT_END_HEADER


#endif /* FTPARAMS_H_ */


/* END */
