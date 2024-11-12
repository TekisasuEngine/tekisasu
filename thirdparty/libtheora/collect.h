/**************************************************************************/
/*  collect.h                                                             */
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
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

  function: mode selection code
  last mod: $Id$

 ********************************************************************/
#if !defined(_collect_H)
# define _collect_H (1)
# include "encint.h"
# if defined(OC_COLLECT_METRICS)
#  include <stdio.h>



typedef struct oc_mode_metrics oc_mode_metrics;



/**Sets the file name to load/store mode metrics from/to.
 * The file name string is stored by reference, and so must be valid for the
 *  lifetime of the encoder.
 * Mode metric collection uses global tables; do not attempt to perform
 *  multiple collections at once.
 * \param[in] _buf <tt>char[]</tt> The file name.
 * \retval TH_EIMPL   Not supported by this implementation.*/
#define TH_ENCCTL_SET_METRICS_FILE (0x8000)



/*Accumulates various weighted sums of the measurements.
  w -> weight
  s -> SATD
  q -> log quantizer
  r -> rate (in bits)
  d -> RMSE
  All of the single letters correspond to direct, weighted sums, e.g.,
   w=sum(w_i), s=sum(s_i*w_i), etc.
  The others correspond to central moments (or co-moments) of the given order,
   e.g., sq=sum((s_i-s/w)*(q_i-q/w)*w_i).
  Because we need some moments up to fourth order, we use central moments to
   minimize the dynamic range and prevent rounding error from dominating the
   calculations.*/
struct oc_mode_metrics{
  double w;
  double s;
  double q;
  double r;
  double d;
  double s2;
  double sq;
  double q2;
  double sr;
  double qr;
  double r2;
  double sd;
  double qd;
  double d2;
  double s2q;
  double sq2;
  double sqr;
  double sqd;
  double s2q2;
};


# define OC_ZWEIGHT   (0.25)

/*TODO: It may be helpful (for block-level quantizers especially) to separate
   out the contributions from AC and DC into separate tables.*/

extern ogg_int16_t OC_MODE_LOGQ[OC_LOGQ_BINS][3][2];
extern oc_mode_rd  OC_MODE_RD_SATD[OC_LOGQ_BINS][3][2][OC_COMP_BINS];
extern oc_mode_rd  OC_MODE_RD_SAD[OC_LOGQ_BINS][3][2][OC_COMP_BINS];

extern int              OC_HAS_MODE_METRICS;
extern oc_mode_metrics  OC_MODE_METRICS_SATD[OC_LOGQ_BINS-1][3][2][OC_COMP_BINS];
extern oc_mode_metrics  OC_MODE_METRICS_SAD[OC_LOGQ_BINS-1][3][2][OC_COMP_BINS];
extern const char      *OC_MODE_METRICS_FILENAME;

void oc_mode_metrics_dump();
void oc_mode_metrics_print(FILE *_fout);

void oc_mode_metrics_add(oc_mode_metrics *_metrics,
 double _w,int _s,int _q,int _r,double _d);
void oc_mode_metrics_merge(oc_mode_metrics *_dst,
 const oc_mode_metrics *_src,int _n);
double oc_mode_metrics_solve(double *_r,double *_d,
 const oc_mode_metrics *_metrics,const int *_s0,const int *_s1,
 const int *_q0,const int *_q1,
 const double *_ra,const double *_rb,const double *_rc,
 const double *_da,const double *_db,const double *_dc,int _n);
void oc_mode_metrics_update(oc_mode_metrics (*_metrics)[3][2][OC_COMP_BINS],
 int _niters_min,int _reweight,oc_mode_rd (*_table)[3][2][OC_COMP_BINS],
 int shift,double (*_weight)[3][2][OC_COMP_BINS]);
void oc_enc_mode_metrics_load(oc_enc_ctx *_enc);
void oc_enc_mode_metrics_collect(oc_enc_ctx *_enc);

# endif
#endif
