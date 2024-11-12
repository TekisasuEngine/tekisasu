/**************************************************************************/
/*  apiwrapper.h                                                          */
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
    last mod: $Id: apiwrapper.h 13596 2007-08-23 20:05:38Z tterribe $

 ********************************************************************/

#if !defined(_apiwrapper_H)
# define _apiwrapper_H (1)
# include <ogg/ogg.h>
# include <theora/theora.h>
# include "theora/theoradec.h"
# include "theora/theoraenc.h"
# include "state.h"

typedef struct th_api_wrapper th_api_wrapper;
typedef struct th_api_info    th_api_info;

/*Provide an entry point for the codec setup to clear itself in case we ever
   want to break pieces off into a common base library shared by encoder and
   decoder.
  In addition, this makes several other pieces of the API wrapper cleaner.*/
typedef void (*oc_setup_clear_func)(void *_ts);

/*Generally only one of these pointers will be non-NULL in any given instance.
  Technically we do not even really need this struct, since we should be able
   to figure out which one from "context", but doing it this way makes sure we
   don't flub it up.*/
struct th_api_wrapper{
  oc_setup_clear_func  clear;
  th_setup_info       *setup;
  th_dec_ctx          *decode;
  th_enc_ctx          *encode;
};

struct th_api_info{
  th_api_wrapper api;
  theora_info    info;
};


void oc_theora_info2th_info(th_info *_info,const theora_info *_ci);

#endif
