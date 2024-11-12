/**************************************************************************/
/*  enquant.h                                                             */
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

#if !defined(_enquant_H)
# define _enquant_H (1)
# include "quant.h"

typedef struct oc_iquant oc_iquant;

#define OC_QUANT_MAX_LOG (OC_Q57(OC_STATIC_ILOG_32(OC_QUANT_MAX)-1))

/*Used to compute x/d via ((x*m>>16)+x>>l)+(x<0))
   (i.e., one 16x16->16 mul, 2 shifts, and 2 adds).
  This is not an approximation; for 16-bit x and d, it is exact.*/
struct oc_iquant{
  ogg_int16_t m;
  ogg_int16_t l;
};



int oc_quant_params_clone(th_quant_info *_dst,const th_quant_info *_src);
void oc_quant_params_pack(oggpack_buffer *_opb,const th_quant_info *_qinfo);
void oc_iquant_init(oc_iquant *_this,ogg_uint16_t _d);
void oc_enquant_qavg_init(ogg_int64_t _log_qavg[2][64],
 ogg_int16_t _log_plq[64][3][2],ogg_uint16_t _pl_rd_scale[2][64][2],
 ogg_uint16_t *_dequant[64][3][2],int _pixel_fmt);

#endif
