/**************************************************************************/
/*  msdf-error-correction.h                                               */
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
#include "Projection.h"
#include "Shape.h"
#include "BitmapRef.hpp"
#include "generator-config.h"

namespace msdfgen {

/// Predicts potential artifacts caused by the interpolation of the MSDF and corrects them by converting nearby texels to single-channel.
void msdfErrorCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Projection &projection, double range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());
void msdfErrorCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Projection &projection, double range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

/// Applies the simplified error correction to all discontiunous distances (INDISCRIMINATE mode). Does not need shape or translation.
void msdfFastDistanceErrorCorrection(const BitmapRef<float, 3> &sdf, const Projection &projection, double range, double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);
void msdfFastDistanceErrorCorrection(const BitmapRef<float, 4> &sdf, const Projection &projection, double range, double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

/// Applies the simplified error correction to edges only (EDGE_ONLY mode). Does not need shape or translation.
void msdfFastEdgeErrorCorrection(const BitmapRef<float, 3> &sdf, const Projection &projection, double range, double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);
void msdfFastEdgeErrorCorrection(const BitmapRef<float, 4> &sdf, const Projection &projection, double range, double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

/// The original version of the error correction algorithm.
void msdfErrorCorrection_legacy(const BitmapRef<float, 3> &output, const Vector2 &threshold);
void msdfErrorCorrection_legacy(const BitmapRef<float, 4> &output, const Vector2 &threshold);

}
