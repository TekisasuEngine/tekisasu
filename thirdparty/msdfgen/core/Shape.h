/**************************************************************************/
/*  Shape.h                                                               */
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

#include <vector>
#include "Contour.h"
#include "Scanline.h"

namespace msdfgen {

// Threshold of the dot product of adjacent edge directions to be considered convergent.
#define MSDFGEN_CORNER_DOT_EPSILON .000001
// The proportional amount by which a curve's control point will be adjusted to eliminate convergent corners.
#define MSDFGEN_DECONVERGENCE_FACTOR .000001

/// Vector shape representation.
class Shape {

public:
    struct Bounds {
        double l, b, r, t;
    };

    /// The list of contours the shape consists of.
    std::vector<Contour> contours;
    /// Specifies whether the shape uses bottom-to-top (false) or top-to-bottom (true) Y coordinates.
    bool inverseYAxis;

    Shape();
    /// Adds a contour.
    void addContour(const Contour &contour);
#ifdef MSDFGEN_USE_CPP11
    void addContour(Contour &&contour);
#endif
    /// Adds a blank contour and returns its reference.
    Contour &addContour();
    /// Normalizes the shape geometry for distance field generation.
    void normalize();
    /// Performs basic checks to determine if the object represents a valid shape.
    bool validate() const;
    /// Adjusts the bounding box to fit the shape.
    void bound(double &l, double &b, double &r, double &t) const;
    /// Adjusts the bounding box to fit the shape border's mitered corners.
    void boundMiters(double &l, double &b, double &r, double &t, double border, double miterLimit, int polarity) const;
    /// Computes the minimum bounding box that fits the shape, optionally with a (mitered) border.
    Bounds getBounds(double border = 0, double miterLimit = 0, int polarity = 0) const;
    /// Outputs the scanline that intersects the shape at y.
    void scanline(Scanline &line, double y) const;
    /// Returns the total number of edge segments
    int edgeCount() const;
    /// Assumes its contours are unoriented (even-odd fill rule). Attempts to orient them to conform to the non-zero winding rule.
    void orientContours();

};

}
