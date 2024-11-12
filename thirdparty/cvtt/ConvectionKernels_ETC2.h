/**************************************************************************/
/*  ConvectionKernels_ETC2.h                                              */
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

#include <stdint.h>

namespace cvtt
{
    namespace Tables
    {
        namespace ETC2
        {
            const int16_t g_thModifierTable[8] =
            {
                3, 6, 11, 16, 23, 32, 41, 64
            };

            const int16_t g_alphaModifierTablePositive[16][4] =
            {
                { 2, 5, 8, 14, },
                { 2, 6, 9, 12, },
                { 1, 4, 7, 12, },
                { 1, 3, 5, 12, },
                { 2, 5, 7, 11, },
                { 2, 6, 8, 10, },
                { 3, 6, 7, 10, },
                { 2, 4, 7, 10, },
                { 1, 5, 7, 9, },
                { 1, 4, 7, 9, },
                { 1, 3, 7, 9, },
                { 1, 4, 6, 9, },
                { 2, 3, 6, 9, },
                { 0, 1, 2, 9, },
                { 3, 5, 7, 8, },
                { 2, 4, 6, 8, },
            };
        }
    }
}
