/**************************************************************************/
/*  edge-segments.h                                                       */
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
#include "SignedDistance.hpp"
#include "EdgeColor.h"

namespace msdfgen {

// Parameters for iterative search of closest point on a cubic Bezier curve. Increase for higher precision.
#define MSDFGEN_CUBIC_SEARCH_STARTS 4
#define MSDFGEN_CUBIC_SEARCH_STEPS 4

/// An abstract edge segment.
class EdgeSegment {

public:
    EdgeColor color;

    EdgeSegment(EdgeColor edgeColor = WHITE) : color(edgeColor) { }
    virtual ~EdgeSegment() { }
    /// Creates a copy of the edge segment.
    virtual EdgeSegment *clone() const = 0;
    /// Returns the numeric code of the edge segment's type.
    virtual int type() const = 0;
    /// Returns the array of control points.
    virtual const Point2 *controlPoints() const = 0;
    /// Returns the point on the edge specified by the parameter (between 0 and 1).
    virtual Point2 point(double param) const = 0;
    /// Returns the direction the edge has at the point specified by the parameter.
    virtual Vector2 direction(double param) const = 0;
    /// Returns the change of direction (second derivative) at the point specified by the parameter.
    virtual Vector2 directionChange(double param) const = 0;
    /// Returns the minimum signed distance between origin and the edge.
    virtual SignedDistance signedDistance(Point2 origin, double &param) const = 0;
    /// Converts a previously retrieved signed distance from origin to pseudo-distance.
    virtual void distanceToPseudoDistance(SignedDistance &distance, Point2 origin, double param) const;
    /// Outputs a list of (at most three) intersections (their X coordinates) with an infinite horizontal scanline at y and returns how many there are.
    virtual int scanlineIntersections(double x[3], int dy[3], double y) const = 0;
    /// Adjusts the bounding box to fit the edge segment.
    virtual void bound(double &l, double &b, double &r, double &t) const = 0;

    /// Reverses the edge (swaps its start point and end point).
    virtual void reverse() = 0;
    /// Moves the start point of the edge segment.
    virtual void moveStartPoint(Point2 to) = 0;
    /// Moves the end point of the edge segment.
    virtual void moveEndPoint(Point2 to) = 0;
    /// Splits the edge segments into thirds which together represent the original edge.
    virtual void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const = 0;

};

/// A line segment.
class LinearSegment : public EdgeSegment {

public:
    enum EdgeType {
        EDGE_TYPE = 1
    };

    Point2 p[2];

    LinearSegment(Point2 p0, Point2 p1, EdgeColor edgeColor = WHITE);
    LinearSegment *clone() const;
    int type() const;
    const Point2 *controlPoints() const;
    Point2 point(double param) const;
    Vector2 direction(double param) const;
    Vector2 directionChange(double param) const;
    double length() const;
    SignedDistance signedDistance(Point2 origin, double &param) const;
    int scanlineIntersections(double x[3], int dy[3], double y) const;
    void bound(double &l, double &b, double &r, double &t) const;

    void reverse();
    void moveStartPoint(Point2 to);
    void moveEndPoint(Point2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;

};

/// A quadratic Bezier curve.
class QuadraticSegment : public EdgeSegment {

public:
    enum EdgeType {
        EDGE_TYPE = 2
    };

    Point2 p[3];

    QuadraticSegment(Point2 p0, Point2 p1, Point2 p2, EdgeColor edgeColor = WHITE);
    QuadraticSegment *clone() const;
    int type() const;
    const Point2 *controlPoints() const;
    Point2 point(double param) const;
    Vector2 direction(double param) const;
    Vector2 directionChange(double param) const;
    double length() const;
    SignedDistance signedDistance(Point2 origin, double &param) const;
    int scanlineIntersections(double x[3], int dy[3], double y) const;
    void bound(double &l, double &b, double &r, double &t) const;

    void reverse();
    void moveStartPoint(Point2 to);
    void moveEndPoint(Point2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;

    EdgeSegment *convertToCubic() const;

};

/// A cubic Bezier curve.
class CubicSegment : public EdgeSegment {

public:
    enum EdgeType {
        EDGE_TYPE = 3
    };

    Point2 p[4];

    CubicSegment(Point2 p0, Point2 p1, Point2 p2, Point2 p3, EdgeColor edgeColor = WHITE);
    CubicSegment *clone() const;
    int type() const;
    const Point2 *controlPoints() const;
    Point2 point(double param) const;
    Vector2 direction(double param) const;
    Vector2 directionChange(double param) const;
    SignedDistance signedDistance(Point2 origin, double &param) const;
    int scanlineIntersections(double x[3], int dy[3], double y) const;
    void bound(double &l, double &b, double &r, double &t) const;

    void reverse();
    void moveStartPoint(Point2 to);
    void moveEndPoint(Point2 to);
    void splitInThirds(EdgeSegment *&part1, EdgeSegment *&part2, EdgeSegment *&part3) const;

    void deconverge(int param, double amount);

};

}
