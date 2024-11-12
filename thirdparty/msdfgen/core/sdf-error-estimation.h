/**************************************************************************/
/*  sdf-error-estimation.h                                                */
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

/// Analytically constructs a scanline at y evaluating fill by linear interpolation of the SDF.
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 1> &sdf, const Projection &projection, double y, bool inverseYAxis = false);
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 3> &sdf, const Projection &projection, double y, bool inverseYAxis = false);
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 4> &sdf, const Projection &projection, double y, bool inverseYAxis = false);

/// Estimates the portion of the area that will be filled incorrectly when rendering using the SDF.
double estimateSDFError(const BitmapConstRef<float, 1> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 3> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 4> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);

// Old version of the function API's kept for backwards compatibility
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 1> &sdf, const Vector2 &scale, const Vector2 &translate, bool inverseYAxis, double y);
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 3> &sdf, const Vector2 &scale, const Vector2 &translate, bool inverseYAxis, double y);
void scanlineSDF(Scanline &line, const BitmapConstRef<float, 4> &sdf, const Vector2 &scale, const Vector2 &translate, bool inverseYAxis, double y);
double estimateSDFError(const BitmapConstRef<float, 1> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 3> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 4> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);

}
