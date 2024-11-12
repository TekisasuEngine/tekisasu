/**************************************************************************/
/*  EdgeHolder.cpp                                                        */
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

#include "EdgeHolder.h"

namespace msdfgen {

void EdgeHolder::swap(EdgeHolder &a, EdgeHolder &b) {
    EdgeSegment *tmp = a.edgeSegment;
    a.edgeSegment = b.edgeSegment;
    b.edgeSegment = tmp;
}

EdgeHolder::EdgeHolder() : edgeSegment(NULL) { }

EdgeHolder::EdgeHolder(EdgeSegment *segment) : edgeSegment(segment) { }

EdgeHolder::EdgeHolder(Point2 p0, Point2 p1, EdgeColor edgeColor) : edgeSegment(new LinearSegment(p0, p1, edgeColor)) { }

EdgeHolder::EdgeHolder(Point2 p0, Point2 p1, Point2 p2, EdgeColor edgeColor) : edgeSegment(new QuadraticSegment(p0, p1, p2, edgeColor)) { }

EdgeHolder::EdgeHolder(Point2 p0, Point2 p1, Point2 p2, Point2 p3, EdgeColor edgeColor) : edgeSegment(new CubicSegment(p0, p1, p2, p3, edgeColor)) { }

EdgeHolder::EdgeHolder(const EdgeHolder &orig) : edgeSegment(orig.edgeSegment ? orig.edgeSegment->clone() : NULL) { }

#ifdef MSDFGEN_USE_CPP11
EdgeHolder::EdgeHolder(EdgeHolder &&orig) : edgeSegment(orig.edgeSegment) {
    orig.edgeSegment = NULL;
}
#endif

EdgeHolder::~EdgeHolder() {
    delete edgeSegment;
}

EdgeHolder &EdgeHolder::operator=(const EdgeHolder &orig) {
    if (this != &orig) {
        delete edgeSegment;
        edgeSegment = orig.edgeSegment ? orig.edgeSegment->clone() : NULL;
    }
    return *this;
}

#ifdef MSDFGEN_USE_CPP11
EdgeHolder &EdgeHolder::operator=(EdgeHolder &&orig) {
    if (this != &orig) {
        delete edgeSegment;
        edgeSegment = orig.edgeSegment;
        orig.edgeSegment = NULL;
    }
    return *this;
}
#endif

EdgeSegment &EdgeHolder::operator*() {
    return *edgeSegment;
}

const EdgeSegment &EdgeHolder::operator*() const {
    return *edgeSegment;
}

EdgeSegment *EdgeHolder::operator->() {
    return edgeSegment;
}

const EdgeSegment *EdgeHolder::operator->() const {
    return edgeSegment;
}

EdgeHolder::operator EdgeSegment *() {
    return edgeSegment;
}

EdgeHolder::operator const EdgeSegment *() const {
    return edgeSegment;
}

}
