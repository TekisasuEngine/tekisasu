/**************************************************************************/
/*  Position.cpp                                                          */
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

// SPDX-License-Identifier: MIT OR MPL-2.0 OR LGPL-2.1-or-later OR GPL-2.0-or-later
// Copyright 2010, SIL International, All rights reserved.

#include "inc/Position.h"
#include <cmath>

using namespace graphite2;

bool Rect::hitTest(Rect &other)
{
    if (bl.x > other.tr.x) return false;
    if (tr.x < other.bl.x) return false;
    if (bl.y > other.tr.y) return false;
    if (tr.y < other.bl.y) return false;
    return true;
}

Position Rect::overlap(Position &offset, Rect &other, Position &othero)
{
    float ax = (bl.x + offset.x) - (other.tr.x + othero.x);
    float ay = (bl.y + offset.y) - (other.tr.y + othero.y);
    float bx = (other.bl.x + othero.x) - (tr.x + offset.x);
    float by = (other.bl.y + othero.y) - (tr.y + offset.y);
    return Position((ax > bx ? ax : bx), (ay > by ? ay : by));
}

float boundmin(float move, float lim1, float lim2, float &error)
{
    // error is always positive for easy comparison
    if (move < lim1 && move < lim2)
    { error = 0.; return move; }
    else if (lim1 < lim2)
    { error = std::fabs(move - lim1); return lim1; }
    else
    { error = std::fabs(move - lim2); return lim2; }
}

#if 0
Position Rect::constrainedAvoid(Position &offset, Rect &box, Rect &sdbox, Position &other, Rect &obox, Rect &osdbox)
{
    // a = max, i = min, s = sum, d = diff
    float eax, eay, eix, eiy, eas, eis, ead, eid;
    float beste = INF;
    Position res;
    // calculate the movements in each direction and the error (amount of remaining overlap)
    // first param is movement, second and third are movement over the constraining box
    float ax = boundmin(obox.tr.x + other.x - box.bl.x - offset.x + 1, tr.x - offset.x, INF, &eax);
    float ay = boundmin(obox.tr.y + other.y - box.bl.y - offset.y + 1, tr.y - offset.y, INF, &eay);
    float ix = boundmin(obox.bl.x + other.x - box.tr.x - offset.x + 1, bl.x - offset.x, INF, &eix);
    float iy = boundmin(obox.bl.y + other.y - box.tr.y - offset.y + 1, bl.y - offset.y, INF, &eiy);
    float as = boundmin(ISQRT2 * (osdbox.tr.x + other.x + other.y - sdbox.bl.x - offset.x - offset.y) + 1, tr.x - offset.x, tr.y - offset.y, &eas);
    float is = boundmin(ISQRT2 * (osdbox.bl.x + other.x + other.y - sdbox.tr.x - offset.x - offset.y) + 1, bl.x - offset.x, bl.y - offset.y, &eis);
    float ad = boundmin(ISQRT2 * (osdbox.tr.y + other.x - other.y - sdbox.bl.y - offset.x + offset.y) + 1, tr.y - offset.y, tr.x - offset.x, &ead);
    float id = boundmin(ISQRT2 * (osdbox.bl.y + other.x - other.y - sdbox.tr.y - offset.x + offset.y) + 1, bl.y - offset.y, bl.x - offset.x, &eid);

    if (eax < beste)
    { res = Position(ax, 0); beste = eax; }
    if (eay < beste)
    { res = Position(0, ay); beste = eay; }
    if (eix < beste)
    { res = Position(ix, 0); beste = eix; }
    if (eiy < beste)
    { res = Position(0, iy); beste = eiy; }
    if (SQRT2 * (eas) < beste)
    { res = Position(as, ad); beste = SQRT2 * (eas); }
    if (SQRT2 * (eis) < beste)
    { res = Position(is, is); beste = SQRT2 * (eis); }
    if (SQRT2 * (ead) < beste)
    { res = Position(ad, ad); beste = SQRT2 * (ead); }
    if (SQRT2 * (eid) < beste)
    { res = Position(id, id); beste = SQRT2 * (eid); }
    return res;
}
#endif
