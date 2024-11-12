/**************************************************************************/
/*  Contour.h                                                             */
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
#include "EdgeHolder.h"

namespace msdfgen {

/// A single closed contour of a shape.
class Contour {

public:
    /// The sequence of edges that make up the contour.
    std::vector<EdgeHolder> edges;

    /// Adds an edge to the contour.
    void addEdge(const EdgeHolder &edge);
#ifdef MSDFGEN_USE_CPP11
    void addEdge(EdgeHolder &&edge);
#endif
    /// Creates a new edge in the contour and returns its reference.
    EdgeHolder &addEdge();
    /// Adjusts the bounding box to fit the contour.
    void bound(double &l, double &b, double &r, double &t) const;
    /// Adjusts the bounding box to fit the contour border's mitered corners.
    void boundMiters(double &l, double &b, double &r, double &t, double border, double miterLimit, int polarity) const;
    /// Computes the winding of the contour. Returns 1 if positive, -1 if negative.
    int winding() const;
    /// Reverses the sequence of edges on the contour.
    void reverse();

};

}
