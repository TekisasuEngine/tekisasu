/**************************************************************************/
/*  render-sdf.cpp                                                        */
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

#include "render-sdf.h"

#include "arithmetics.hpp"
#include "pixel-conversion.hpp"
#include "bitmap-interpolation.hpp"

namespace msdfgen {

static float distVal(float dist, double pxRange, float midValue) {
    if (!pxRange)
        return (float) (dist > midValue);
    return (float) clamp((dist-midValue)*pxRange+.5);
}

void renderSDF(const BitmapRef<float, 1> &output, const BitmapConstRef<float, 1> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd;
            interpolate(&sd, sdf, scale*Point2(x+.5, y+.5));
            *output(x, y) = distVal(sd, pxRange, midValue);
        }
}

void renderSDF(const BitmapRef<float, 3> &output, const BitmapConstRef<float, 1> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd;
            interpolate(&sd, sdf, scale*Point2(x+.5, y+.5));
            float v = distVal(sd, pxRange, midValue);
            output(x, y)[0] = v;
            output(x, y)[1] = v;
            output(x, y)[2] = v;
        }
}

void renderSDF(const BitmapRef<float, 1> &output, const BitmapConstRef<float, 3> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd[3];
            interpolate(sd, sdf, scale*Point2(x+.5, y+.5));
            *output(x, y) = distVal(median(sd[0], sd[1], sd[2]), pxRange, midValue);
        }
}

void renderSDF(const BitmapRef<float, 3> &output, const BitmapConstRef<float, 3> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd[3];
            interpolate(sd, sdf, scale*Point2(x+.5, y+.5));
            output(x, y)[0] = distVal(sd[0], pxRange, midValue);
            output(x, y)[1] = distVal(sd[1], pxRange, midValue);
            output(x, y)[2] = distVal(sd[2], pxRange, midValue);
        }
}

void renderSDF(const BitmapRef<float, 1> &output, const BitmapConstRef<float, 4> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd[4];
            interpolate(sd, sdf, scale*Point2(x+.5, y+.5));
            *output(x, y) = distVal(median(sd[0], sd[1], sd[2]), pxRange, midValue);
        }
}

void renderSDF(const BitmapRef<float, 4> &output, const BitmapConstRef<float, 4> &sdf, double pxRange, float midValue) {
    Vector2 scale((double) sdf.width/output.width, (double) sdf.height/output.height);
    pxRange *= (double) (output.width+output.height)/(sdf.width+sdf.height);
    for (int y = 0; y < output.height; ++y)
        for (int x = 0; x < output.width; ++x) {
            float sd[4];
            interpolate(sd, sdf, scale*Point2(x+.5, y+.5));
            output(x, y)[0] = distVal(sd[0], pxRange, midValue);
            output(x, y)[1] = distVal(sd[1], pxRange, midValue);
            output(x, y)[2] = distVal(sd[2], pxRange, midValue);
            output(x, y)[3] = distVal(sd[3], pxRange, midValue);
        }
}

void simulate8bit(const BitmapRef<float, 1> &bitmap) {
    const float *end = bitmap.pixels+1*bitmap.width*bitmap.height;
    for (float *p = bitmap.pixels; p < end; ++p)
        *p = pixelByteToFloat(pixelFloatToByte(*p));
}

void simulate8bit(const BitmapRef<float, 3> &bitmap) {
    const float *end = bitmap.pixels+3*bitmap.width*bitmap.height;
    for (float *p = bitmap.pixels; p < end; ++p)
        *p = pixelByteToFloat(pixelFloatToByte(*p));
}

void simulate8bit(const BitmapRef<float, 4> &bitmap) {
    const float *end = bitmap.pixels+4*bitmap.width*bitmap.height;
    for (float *p = bitmap.pixels; p < end; ++p)
        *p = pixelByteToFloat(pixelFloatToByte(*p));
}

}
