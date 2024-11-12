/**************************************************************************/
/*  afcover.h                                                             */
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
 * afcover.h
 *
 *   Auto-fitter coverages (specification only).
 *
 * Copyright (C) 2013-2023 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


  /* This header file can be included multiple times. */
  /* Define `COVERAGE' as needed.                     */


  /* Add new coverages here.  The first and second arguments are the   */
  /* coverage name in lowercase and uppercase, respectively, followed  */
  /* by a description string.  The last four arguments are the four    */
  /* characters defining the corresponding OpenType feature.           */

#if 0
  /* XXX: It's not possible to define blue zone characters in advance. */
  COVERAGE( alternative_fractions, ALTERNATIVE_FRACTIONS,
            "alternative fractions",
            'a', 'f', 'r', 'c' )
#endif

  COVERAGE( petite_capitals_from_capitals, PETITE_CAPITALS_FROM_CAPITALS,
            "petite capitals from capitals",
            'c', '2', 'c', 'p' )

  COVERAGE( small_capitals_from_capitals, SMALL_CAPITALS_FROM_CAPITALS,
            "small capitals from capitals",
            'c', '2', 's', 'c' )

#if 0
  /* XXX: Only digits are in this coverage, however, both normal style */
  /*      and oldstyle representation forms are possible.              */
  COVERAGE( denominators, DENOMINATORS,
            "denominators",
            'd', 'n', 'o', 'm' )
#endif

#if 0
  /* XXX: It's not possible to define blue zone characters in advance. */
  COVERAGE( fractions, FRACTIONS,
            "fractions",
            'f', 'r', 'a', 'c' )
#endif

#if 0
  /* XXX: Only digits are in this coverage, however, both normal style */
  /*      and oldstyle representation forms are possible.              */
  COVERAGE( numerators, NUMERATORS,
            "numerators",
            'n', 'u', 'm', 'r' )
#endif

  COVERAGE( ordinals, ORDINALS,
            "ordinals",
            'o', 'r', 'd', 'n' )

  COVERAGE( petite_capitals, PETITE_CAPITALS,
            "petite capitals",
            'p', 'c', 'a', 'p' )

  COVERAGE( ruby, RUBY,
            "ruby",
            'r', 'u', 'b', 'y' )

  COVERAGE( scientific_inferiors, SCIENTIFIC_INFERIORS,
            "scientific inferiors",
            's', 'i', 'n', 'f' )

  COVERAGE( small_capitals, SMALL_CAPITALS,
            "small capitals",
            's', 'm', 'c', 'p' )

  COVERAGE( subscript, SUBSCRIPT,
            "subscript",
            's', 'u', 'b', 's' )

  COVERAGE( superscript, SUPERSCRIPT,
            "superscript",
            's', 'u', 'p', 's' )

  COVERAGE( titling, TITLING,
            "titling",
            't', 'i', 't', 'l' )

#if 0
  /* to be always excluded */
  COVERAGE(nalt, 'n', 'a', 'l', 't'); /* Alternate Annotation Forms (?) */
  COVERAGE(ornm, 'o', 'r', 'n', 'm'); /* Ornaments (?) */
#endif


/* END */
