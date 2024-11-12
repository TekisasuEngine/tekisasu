/**************************************************************************/
/*  ConvectionKernels_BC6H_IO.h                                           */
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

#pragma once

#include <stdint.h>
#include "ConvectionKernels_BC6H_IO.h"

namespace cvtt
{
    namespace BC6H_IO
    {
        typedef void (*ReadFunc_t)(const uint32_t *encoded, uint16_t &d, uint16_t &rw, uint16_t &rx, uint16_t &ry, uint16_t &rz, uint16_t &gw, uint16_t &gx, uint16_t &gy, uint16_t &gz, uint16_t &bw, uint16_t &bx, uint16_t &by, uint16_t &bz);
        typedef void (*WriteFunc_t)(uint32_t *encoded, uint16_t m, uint16_t d, uint16_t rw, uint16_t rx, uint16_t ry, uint16_t rz, uint16_t gw, uint16_t gx, uint16_t gy, uint16_t gz, uint16_t bw, uint16_t bx, uint16_t by, uint16_t bz);

        extern const ReadFunc_t g_readFuncs[14];
        extern const WriteFunc_t g_writeFuncs[14];
    }
}
