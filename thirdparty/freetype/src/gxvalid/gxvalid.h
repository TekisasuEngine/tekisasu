/**************************************************************************/
/*  gxvalid.h                                                             */
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
 * gxvalid.h
 *
 *   TrueTypeGX/AAT table validation (specification only).
 *
 * Copyright (C) 2005-2023 by
 * suzuki toshiya, Masatake YAMATO, Red Hat K.K.,
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

/****************************************************************************
 *
 * gxvalid is derived from both gxlayout module and otvalid module.
 * Development of gxlayout is supported by the Information-technology
 * Promotion Agency(IPA), Japan.
 *
 */


#ifndef GXVALID_H_
#define GXVALID_H_

#include <freetype/freetype.h>

#include "gxverror.h"                     /* must come before `ftvalid.h' */

#include <freetype/internal/ftvalid.h>
#include <freetype/internal/ftstream.h>


FT_BEGIN_HEADER


  FT_LOCAL( void )
  gxv_feat_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );


  FT_LOCAL( void )
  gxv_bsln_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );


  FT_LOCAL( void )
  gxv_trak_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_just_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_mort_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_morx_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_kern_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_kern_validate_classic( FT_Bytes      table,
                             FT_Face       face,
                             FT_Int        dialect_flags,
                             FT_Validator  valid );

  FT_LOCAL( void )
  gxv_opbd_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_prop_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );

  FT_LOCAL( void )
  gxv_lcar_validate( FT_Bytes      table,
                     FT_Face       face,
                     FT_Validator  valid );


FT_END_HEADER


#endif /* GXVALID_H_ */


/* END */
