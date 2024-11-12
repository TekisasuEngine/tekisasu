/**************************************************************************/
/*  edge-coloring.h                                                       */
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

#include "Shape.h"

#define MSDFGEN_EDGE_LENGTH_PRECISION 4

namespace msdfgen {

/** Assigns colors to edges of the shape in accordance to the multi-channel distance field technique.
 *  May split some edges if necessary.
 *  angleThreshold specifies the maximum angle (in radians) to be considered a corner, for example 3 (~172 degrees).
 *  Values below 1/2 PI will be treated as the external angle.
 */
void edgeColoringSimple(Shape &shape, double angleThreshold, unsigned long long seed = 0);

/** The alternative "ink trap" coloring strategy is designed for better results with typefaces
 *  that use ink traps as a design feature. It guarantees that even if all edges that are shorter than
 *  both their neighboring edges are removed, the coloring remains consistent with the established rules.
 */
void edgeColoringInkTrap(Shape &shape, double angleThreshold, unsigned long long seed = 0);

/** The alternative coloring by distance tries to use different colors for edges that are close together.
 *  This should theoretically be the best strategy on average. However, since it needs to compute the distance
 *  between all pairs of edges, and perform a graph optimization task, it is much slower than the rest.
 */
void edgeColoringByDistance(Shape &shape, double angleThreshold, unsigned long long seed = 0);

}
