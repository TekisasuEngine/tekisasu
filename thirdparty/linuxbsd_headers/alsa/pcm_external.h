/**************************************************************************/
/*  pcm_external.h                                                        */
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

/**
 * \file include/pcm_external.h
 * \brief External PCM plugin SDK
 * \author Takashi Iwai <tiwai@suse.de>
 * \date 2005
 *
 * Extern PCM plugin SDK.
 */

/*
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#ifndef __ALSA_PCM_EXTERNAL_H
#define __ALSA_PCM_EXTERNAL_H

#include "pcm.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup Plugin_SDK External PCM plugin SDK
 *  \{
 */

/**
 * Define the object entry for external PCM plugins
 */
#define SND_PCM_PLUGIN_ENTRY(name) _snd_pcm_##name##_open

/**
 * Define the symbols of the given plugin with versions
 */
#define SND_PCM_PLUGIN_SYMBOL(name) SND_DLSYM_BUILD_VERSION(SND_PCM_PLUGIN_ENTRY(name), SND_PCM_DLSYM_VERSION);

/**
 * Define the plugin
 */
#define SND_PCM_PLUGIN_DEFINE_FUNC(plugin) \
int SND_PCM_PLUGIN_ENTRY(plugin) (snd_pcm_t **pcmp, const char *name,\
				  snd_config_t *root, snd_config_t *conf, \
				  snd_pcm_stream_t stream, int mode)

#include "pcm_ioplug.h"
#include "pcm_extplug.h"

int snd_pcm_parse_control_id(snd_config_t *conf, snd_ctl_elem_id_t *ctl_id, int *cardp,
			     int *cchannelsp, int *hwctlp);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* __ALSA_PCM_EXTERNAL_H */
