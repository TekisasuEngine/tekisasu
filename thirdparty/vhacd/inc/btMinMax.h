/**************************************************************************/
/*  btMinMax.h                                                            */
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

/*
Copyright (c) 2003-2006 Gino van den Bergen / Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_GEN_MINMAX_H
#define BT_GEN_MINMAX_H

#include "btScalar.h"

// -- GODOT start --
namespace VHACD {
// -- GODOT end --

template <class T>
SIMD_FORCE_INLINE const T& btMin(const T& a, const T& b)
{
    return a < b ? a : b;
}

template <class T>
SIMD_FORCE_INLINE const T& btMax(const T& a, const T& b)
{
    return a > b ? a : b;
}

template <class T>
SIMD_FORCE_INLINE const T& btClamped(const T& a, const T& lb, const T& ub)
{
    return a < lb ? lb : (ub < a ? ub : a);
}

template <class T>
SIMD_FORCE_INLINE void btSetMin(T& a, const T& b)
{
    if (b < a) {
        a = b;
    }
}

template <class T>
SIMD_FORCE_INLINE void btSetMax(T& a, const T& b)
{
    if (a < b) {
        a = b;
    }
}

template <class T>
SIMD_FORCE_INLINE void btClamp(T& a, const T& lb, const T& ub)
{
    if (a < lb) {
        a = lb;
    }
    else if (ub < a) {
        a = ub;
    }
}

// -- GODOT start --
}; // namespace VHACD
// -- GODOT end --

#endif //BT_GEN_MINMAX_H
