/**************************************************************************/
/*  rasterization.h                                                       */
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

#include "Vector2.hpp"
#include "Shape.h"
#include "Projection.h"
#include "Scanline.h"
#include "BitmapRef.hpp"

namespace msdfgen {

/// Rasterizes the shape into a monochrome bitmap.
void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
/// Fixes the sign of the input signed distance field, so that it matches the shape's rasterized fill.
void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);

// Old version of the function API's kept for backwards compatibility
void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule = FILL_NONZERO);

}
