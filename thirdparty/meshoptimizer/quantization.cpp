/**************************************************************************/
/*  quantization.cpp                                                      */
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

// This file is part of meshoptimizer library; see meshoptimizer.h for version/license details
#include "meshoptimizer.h"

#include <assert.h>

unsigned short meshopt_quantizeHalf(float v)
{
	union { float f; unsigned int ui; } u = {v};
	unsigned int ui = u.ui;

	int s = (ui >> 16) & 0x8000;
	int em = ui & 0x7fffffff;

	// bias exponent and round to nearest; 112 is relative exponent bias (127-15)
	int h = (em - (112 << 23) + (1 << 12)) >> 13;

	// underflow: flush to zero; 113 encodes exponent -14
	h = (em < (113 << 23)) ? 0 : h;

	// overflow: infinity; 143 encodes exponent 16
	h = (em >= (143 << 23)) ? 0x7c00 : h;

	// NaN; note that we convert all types of NaN to qNaN
	h = (em > (255 << 23)) ? 0x7e00 : h;

	return (unsigned short)(s | h);
}

float meshopt_quantizeFloat(float v, int N)
{
	assert(N >= 0 && N <= 23);

	union { float f; unsigned int ui; } u = {v};
	unsigned int ui = u.ui;

	const int mask = (1 << (23 - N)) - 1;
	const int round = (1 << (23 - N)) >> 1;

	int e = ui & 0x7f800000;
	unsigned int rui = (ui + round) & ~mask;

	// round all numbers except inf/nan; this is important to make sure nan doesn't overflow into -0
	ui = e == 0x7f800000 ? ui : rui;

	// flush denormals to zero
	ui = e == 0 ? 0 : ui;

	u.ui = ui;
	return u.f;
}

float meshopt_dequantizeHalf(unsigned short h)
{
	unsigned int s = unsigned(h & 0x8000) << 16;
	int em = h & 0x7fff;

	// bias exponent and pad mantissa with 0; 112 is relative exponent bias (127-15)
	int r = (em + (112 << 10)) << 13;

	// denormal: flush to zero
	r = (em < (1 << 10)) ? 0 : r;

	// infinity/NaN; note that we preserve NaN payload as a byproduct of unifying inf/nan cases
	// 112 is an exponent bias fixup; since we already applied it once, applying it twice converts 31 to 255
	r += (em >= (31 << 10)) ? (112 << 23) : 0;

	union { float f; unsigned int ui; } u;
	u.ui = s | r;
	return u.f;
}
