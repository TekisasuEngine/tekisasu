/**************************************************************************/
/*  ttcmapc.h                                                             */
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
 * ttcmapc.h
 *
 *   TT CMAP classes definitions (specification only).
 *
 * Copyright (C) 2009-2023 by
 * Oran Agra and Mickey Gabel.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifdef TT_CONFIG_CMAP_FORMAT_0
  TTCMAPCITEM( tt_cmap0_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_2
  TTCMAPCITEM( tt_cmap2_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_4
  TTCMAPCITEM( tt_cmap4_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_6
  TTCMAPCITEM( tt_cmap6_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_8
  TTCMAPCITEM( tt_cmap8_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_10
  TTCMAPCITEM( tt_cmap10_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_12
  TTCMAPCITEM( tt_cmap12_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_13
  TTCMAPCITEM( tt_cmap13_class_rec )
#endif

#ifdef TT_CONFIG_CMAP_FORMAT_14
  TTCMAPCITEM( tt_cmap14_class_rec )
#endif


  /* END */
