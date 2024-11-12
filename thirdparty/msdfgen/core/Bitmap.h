/**************************************************************************/
/*  Bitmap.h                                                              */
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

#include "BitmapRef.hpp"

namespace msdfgen {

/// A 2D image bitmap with N channels of type T. Pixel memory is managed by the class.
template <typename T, int N = 1>
class Bitmap {

public:
    Bitmap();
    Bitmap(int width, int height);
    Bitmap(const BitmapConstRef<T, N> &orig);
    Bitmap(const Bitmap<T, N> &orig);
#ifdef MSDFGEN_USE_CPP11
    Bitmap(Bitmap<T, N> &&orig);
#endif
    ~Bitmap();
    Bitmap<T, N> &operator=(const BitmapConstRef<T, N> &orig);
    Bitmap<T, N> &operator=(const Bitmap<T, N> &orig);
#ifdef MSDFGEN_USE_CPP11
    Bitmap<T, N> &operator=(Bitmap<T, N> &&orig);
#endif
    /// Bitmap width in pixels.
    int width() const;
    /// Bitmap height in pixels.
    int height() const;
    T *operator()(int x, int y);
    const T *operator()(int x, int y) const;
#ifdef MSDFGEN_USE_CPP11
    explicit operator T *();
    explicit operator const T *() const;
#else
    operator T *();
    operator const T *() const;
#endif
    operator BitmapRef<T, N>();
    operator BitmapConstRef<T, N>() const;

private:
    T *pixels;
    int w, h;

};

}

#include "Bitmap.hpp"
