/**************************************************************************/
/*  MSDFErrorCorrection.h                                                 */
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

#include "Projection.h"
#include "Shape.h"
#include "BitmapRef.hpp"

namespace msdfgen {

/// Performs error correction on a computed MSDF to eliminate interpolation artifacts. This is a low-level class, you may want to use the API in msdf-error-correction.h instead.
class MSDFErrorCorrection {

public:
    /// Stencil flags.
    enum Flags {
        /// Texel marked as potentially causing interpolation errors.
        ERROR = 1,
        /// Texel marked as protected. Protected texels are only given the error flag if they cause inversion artifacts.
        PROTECTED = 2
    };

    MSDFErrorCorrection();
    explicit MSDFErrorCorrection(const BitmapRef<byte, 1> &stencil, const Projection &projection, double range);
    /// Sets the minimum ratio between the actual and maximum expected distance delta to be considered an error.
    void setMinDeviationRatio(double minDeviationRatio);
    /// Sets the minimum ratio between the pre-correction distance error and the post-correction distance error.
    void setMinImproveRatio(double minImproveRatio);
    /// Flags all texels that are interpolated at corners as protected.
    void protectCorners(const Shape &shape);
    /// Flags all texels that contribute to edges as protected.
    template <int N>
    void protectEdges(const BitmapConstRef<float, N> &sdf);
    /// Flags all texels as protected.
    void protectAll();
    /// Flags texels that are expected to cause interpolation artifacts based on analysis of the SDF only.
    template <int N>
    void findErrors(const BitmapConstRef<float, N> &sdf);
    /// Flags texels that are expected to cause interpolation artifacts based on analysis of the SDF and comparison with the exact shape distance.
    template <template <typename> class ContourCombiner, int N>
    void findErrors(const BitmapConstRef<float, N> &sdf, const Shape &shape);
    /// Modifies the MSDF so that all texels with the error flag are converted to single-channel.
    template <int N>
    void apply(const BitmapRef<float, N> &sdf) const;
    /// Returns the stencil in its current state (see Flags).
    BitmapConstRef<byte, 1> getStencil() const;

private:
    BitmapRef<byte, 1> stencil;
    Projection projection;
    double invRange;
    double minDeviationRatio;
    double minImproveRatio;

};

}
