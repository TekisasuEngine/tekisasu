/**************************************************************************/
/*  generator-config.h                                                    */
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

#ifndef MSDFGEN_PUBLIC
#define MSDFGEN_PUBLIC // for DLL import/export
#endif

namespace msdfgen {

/// The configuration of the MSDF error correction pass.
struct ErrorCorrectionConfig {
    /// The default value of minDeviationRatio.
    static MSDFGEN_PUBLIC const double defaultMinDeviationRatio;
    /// The default value of minImproveRatio.
    static MSDFGEN_PUBLIC const double defaultMinImproveRatio;

    /// Mode of operation.
    enum Mode {
        /// Skips error correction pass.
        DISABLED,
        /// Corrects all discontinuities of the distance field regardless if edges are adversely affected.
        INDISCRIMINATE,
        /// Corrects artifacts at edges and other discontinuous distances only if it does not affect edges or corners.
        EDGE_PRIORITY,
        /// Only corrects artifacts at edges.
        EDGE_ONLY
    } mode;
    /// Configuration of whether to use an algorithm that computes the exact shape distance at the positions of suspected artifacts. This algorithm can be much slower.
    enum DistanceCheckMode {
        /// Never computes exact shape distance.
        DO_NOT_CHECK_DISTANCE,
        /// Only computes exact shape distance at edges. Provides a good balance between speed and precision.
        CHECK_DISTANCE_AT_EDGE,
        /// Computes and compares the exact shape distance for each suspected artifact.
        ALWAYS_CHECK_DISTANCE
    } distanceCheckMode;
    /// The minimum ratio between the actual and maximum expected distance delta to be considered an error.
    double minDeviationRatio;
    /// The minimum ratio between the pre-correction distance error and the post-correction distance error. Has no effect for DO_NOT_CHECK_DISTANCE.
    double minImproveRatio;
    /// An optional buffer to avoid dynamic allocation. Must have at least as many bytes as the MSDF has pixels.
    byte *buffer;

    inline explicit ErrorCorrectionConfig(Mode mode = EDGE_PRIORITY, DistanceCheckMode distanceCheckMode = CHECK_DISTANCE_AT_EDGE, double minDeviationRatio = defaultMinDeviationRatio, double minImproveRatio = defaultMinImproveRatio, byte *buffer = NULL) : mode(mode), distanceCheckMode(distanceCheckMode), minDeviationRatio(minDeviationRatio), minImproveRatio(minImproveRatio), buffer(buffer) { }
};

/// The configuration of the distance field generator algorithm.
struct GeneratorConfig {
    /// Specifies whether to use the version of the algorithm that supports overlapping contours with the same winding. May be set to false to improve performance when no such contours are present.
    bool overlapSupport;

    inline explicit GeneratorConfig(bool overlapSupport = true) : overlapSupport(overlapSupport) { }
};

/// The configuration of the multi-channel distance field generator algorithm.
struct MSDFGeneratorConfig : GeneratorConfig {
    /// Configuration of the error correction pass.
    ErrorCorrectionConfig errorCorrection;

    inline MSDFGeneratorConfig() { }
    inline explicit MSDFGeneratorConfig(bool overlapSupport, const ErrorCorrectionConfig &errorCorrection = ErrorCorrectionConfig()) : GeneratorConfig(overlapSupport), errorCorrection(errorCorrection) { }
};

}
