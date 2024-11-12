/**************************************************************************/
/*  codelength.h                                                          */
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

/* $Id: codelength.h,v 1.3 2011/07/30 13:10:05 nanard Exp $ */
/* Project : miniupnp
 * Author : Thomas BERNARD
 * copyright (c) 2005-2015 Thomas Bernard
 * This software is subjet to the conditions detailed in the
 * provided LICENCE file. */
#ifndef CODELENGTH_H_INCLUDED
#define CODELENGTH_H_INCLUDED

/* Encode length by using 7bit per Byte :
 * Most significant bit of each byte specifies that the
 * following byte is part of the code */

/* n : unsigned
 * p : unsigned char *
 */
#define DECODELENGTH(n, p) n = 0; \
                           do { n = (n << 7) | (*p & 0x7f); } \
                           while((*(p++)&0x80) && (n<(1<<25)));

/* n :    unsigned
 * READ : function/macro to read one byte (unsigned char)
 */
#define DECODELENGTH_READ(n, READ) \
	n = 0; \
	do { \
		unsigned char c; \
		READ(c); \
		n = (n << 7) | (c & 0x07f); \
		if(!(c&0x80)) break; \
	} while(n<(1<<25));

/* n :       unsigned
 * p :       unsigned char *
 * p_limit : unsigned char *
 */
#define DECODELENGTH_CHECKLIMIT(n, p, p_limit) \
	n = 0; \
	do { \
		if((p) >= (p_limit)) break; \
		n = (n << 7) | (*(p) & 0x7f); \
	} while((*((p)++)&0x80) && (n<(1<<25)));


/* n : unsigned
 * p : unsigned char *
 */
#define CODELENGTH(n, p) if(n>=268435456) *(p++) = (n >> 28) | 0x80; \
                         if(n>=2097152) *(p++) = (n >> 21) | 0x80; \
                         if(n>=16384) *(p++) = (n >> 14) | 0x80; \
                         if(n>=128) *(p++) = (n >> 7) | 0x80; \
                         *(p++) = n & 0x7f;

#endif /* CODELENGTH_H_INCLUDED */
