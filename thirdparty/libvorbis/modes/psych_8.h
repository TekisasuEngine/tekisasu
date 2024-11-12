/**************************************************************************/
/*  psych_8.h                                                             */
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
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2009             *
 * by the Xiph.Org Foundation https://xiph.org/                     *
 *                                                                  *
 ********************************************************************

 function: 8kHz psychoacoustic settings

 ********************************************************************/

static const att3 _psy_tone_masteratt_8[3]={
  {{ 32,  25,  12},  0,   0},  /* 0 */
  {{ 30,  25,  12},  0,   0},  /* 0 */
  {{ 20,   0, -14},  0,   0}, /* 0 */
};

static const vp_adjblock _vp_tonemask_adj_8[3]={
  /* adjust for mode zero */
  /* 63     125     250     500     1     2     4     8    16 */
  {{-15,-15,-15,-15,-10,-10, -6, 0, 0, 0, 0,10, 0, 0,99,99,99}}, /* 1 */
  {{-15,-15,-15,-15,-10,-10, -6, 0, 0, 0, 0,10, 0, 0,99,99,99}}, /* 1 */
  {{-15,-15,-15,-15,-10,-10, -6, 0, 0, 0, 0, 0, 0, 0,99,99,99}}, /* 1 */
};


static const noise3 _psy_noisebias_8[3]={
  /*  63     125     250     500      1k       2k      4k      8k     16k*/
  {{{-10,-10,-10,-10, -5, -5, -5,  0,  4,  8,  8,  8, 10, 10, 99, 99, 99},
    {-10,-10,-10,-10, -5, -5, -5,  0,  0,  4,  4,  4,  4,  4, 99, 99, 99},
    {-30,-30,-30,-30,-30,-24,-20,-14,-10, -6, -8, -8, -6, -6, 99, 99, 99}}},

  {{{-10,-10,-10,-10, -5, -5, -5,  0,  4,  8,  8,  8, 10, 10, 99, 99, 99},
    {-10,-10,-10,-10,-10,-10, -5, -5, -5,  0,  0,  0,  0,  0, 99, 99, 99},
    {-30,-30,-30,-30,-30,-24,-20,-14,-10, -6, -8, -8, -6, -6, 99, 99, 99}}},

  {{{-15,-15,-15,-15,-15,-12,-10, -8,  0,  2,  4,  4,  5,  5, 99, 99, 99},
    {-30,-30,-30,-30,-26,-22,-20,-14,-12,-12,-10,-10,-10,-10, 99, 99, 99},
    {-30,-30,-30,-30,-26,-26,-26,-26,-26,-26,-26,-26,-26,-24, 99, 99, 99}}},
};

/* stereo mode by base quality level */
static const adj_stereo _psy_stereo_modes_8[3]={
  /*  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  */
  {{  4,  4,  4,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3},
   {  6,  5,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
   {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
   { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}},
  {{  4,  4,  4,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3},
   {  6,  5,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
   {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
   { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}},
  {{  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3},
   {  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
   {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
   { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}},
};

static const noiseguard _psy_noiseguards_8[2]={
  {10,10,-1},
  {10,10,-1},
};

static const compandblock _psy_compand_8[2]={
  {{
     0, 1, 2, 3, 4, 5, 6,  7,     /* 7dB */
     8, 8, 9, 9,10,10,11, 11,     /* 15dB */
    12,12,13,13,14,14,15, 15,     /* 23dB */
    16,16,17,17,17,18,18, 19,     /* 31dB */
    19,19,20,21,22,23,24, 25,     /* 39dB */
  }},
  {{
     0, 1, 2, 3, 4, 5, 6,  6,     /* 7dB */
     7, 7, 6, 6, 5, 5, 4,  4,     /* 15dB */
     3, 3, 3, 4, 5, 6, 7,  8,     /* 23dB */
     9,10,11,12,13,14,15, 16,     /* 31dB */
    17,18,19,20,21,22,23, 24,     /* 39dB */
  }},
};

static const double _psy_lowpass_8[3]={3.,4.,4.};
static const int _noise_start_8[2]={
  64,64,
};
static const int _noise_part_8[2]={
  8,8,
};

static const int _psy_ath_floater_8[3]={
  -100,-100,-105,
};

static const int _psy_ath_abs_8[3]={
  -130,-130,-140,
};
