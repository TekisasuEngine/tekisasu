/**************************************************************************/
/*  input.h                                                               */
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
 * \file include/input.h
 * \brief Application interface library for the ALSA driver
 * \author Jaroslav Kysela <perex@perex.cz>
 * \author Abramo Bagnara <abramo@alsa-project.org>
 * \author Takashi Iwai <tiwai@suse.de>
 * \date 1998-2001
 *
 * Application interface library for the ALSA driver
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

#ifndef __ALSA_INPUT_H
#define __ALSA_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup Input Input Interface
 *
 *  The input functions present an interface similar to the stdio functions
 *  on top of different underlying input sources.
 *
 *  The #snd_config_load function uses such an input handle to be able to
 *  load configurations not only from standard files but also from other
 *  sources, e.g. from memory buffers.
 *
 *  \{
 */

/**
 * \brief Internal structure for an input object.
 *
 * The ALSA library uses a pointer to this structure as a handle to an
 * input object. Applications don't access its contents directly.
 */
typedef struct _snd_input snd_input_t;

/** Input type. */
typedef enum _snd_input_type {
	/** Input from a stdio stream. */
	SND_INPUT_STDIO,
	/** Input from a memory buffer. */
	SND_INPUT_BUFFER
} snd_input_type_t;

int snd_input_stdio_open(snd_input_t **inputp, const char *file, const char *mode);
int snd_input_stdio_attach(snd_input_t **inputp, FILE *fp, int _close);
int snd_input_buffer_open(snd_input_t **inputp, const char *buffer, ssize_t size);
int snd_input_close(snd_input_t *input);
int snd_input_scanf(snd_input_t *input, const char *format, ...)
#ifndef DOC_HIDDEN
	__attribute__ ((format (scanf, 2, 3)))
#endif
	;
char *snd_input_gets(snd_input_t *input, char *str, size_t size);
int snd_input_getc(snd_input_t *input);
int snd_input_ungetc(snd_input_t *input, int c);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* __ALSA_INPUT_H */
