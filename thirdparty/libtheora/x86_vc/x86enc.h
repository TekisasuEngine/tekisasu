/**************************************************************************/
/*  x86enc.h                                                              */
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

 *                                                                  *
 * THIS FILE IS PART OF THE OggTheora SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE Theora SOURCE CODE IS COPYRIGHT (C) 2002-2009                *
 * by the Xiph.Org Foundation and contributors http://www.xiph.org/ *
 *                                                                  *
 ********************************************************************

  function:
    last mod: $Id: x86int.h 15675 2009-02-06 09:43:27Z tterribe $

 ********************************************************************/

#if !defined(_x86_vc_x86enc_H)
# define _x86_vc_x86enc_H (1)
# include "x86int.h"
# if defined(OC_X86_ASM)
#  define oc_enc_accel_init oc_enc_accel_init_x86
#  define OC_ENC_USE_VTABLE (1)
# endif
# include "../encint.h"

void oc_enc_accel_init_x86(oc_enc_ctx *_enc);

unsigned oc_enc_frag_sad_mmxext(const unsigned char *_src,
 const unsigned char *_ref,int _ystride);
unsigned oc_enc_frag_sad_thresh_mmxext(const unsigned char *_src,
 const unsigned char *_ref,int _ystride,unsigned _thresh);
unsigned oc_enc_frag_sad2_thresh_mmxext(const unsigned char *_src,
 const unsigned char *_ref1,const unsigned char *_ref2,int _ystride,
 unsigned _thresh);
unsigned oc_enc_frag_satd_mmxext(unsigned *_dc,const unsigned char *_src,
 const unsigned char *_ref,int _ystride);
unsigned oc_enc_frag_satd2_mmxext(unsigned *_dc,const unsigned char *_src,
 const unsigned char *_ref1,const unsigned char *_ref2,int _ystride);
unsigned oc_enc_frag_intra_satd_mmxext(unsigned *_dc,
 const unsigned char *_src,int _ystride);
void oc_enc_frag_sub_mmx(ogg_int16_t _diff[64],
 const unsigned char *_x,const unsigned char *_y,int _stride);
void oc_enc_frag_sub_128_mmx(ogg_int16_t _diff[64],
 const unsigned char *_x,int _stride);
void oc_enc_frag_copy2_mmxext(unsigned char *_dst,
 const unsigned char *_src1,const unsigned char *_src2,int _ystride);
void oc_enc_fdct8x8_mmxext(ogg_int16_t _y[64],const ogg_int16_t _x[64]);
void oc_enc_fdct8x8_x86_64sse2(ogg_int16_t _y[64],const ogg_int16_t _x[64]);

#endif
