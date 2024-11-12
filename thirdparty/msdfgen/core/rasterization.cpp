/**************************************************************************/
/*  rasterization.cpp                                                     */
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

#include "rasterization.h"

#include <vector>
#include "arithmetics.hpp"

namespace msdfgen {

void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const Projection &projection, FillRule fillRule) {
    Scanline scanline;
    for (int y = 0; y < output.height; ++y) {
        int row = shape.inverseYAxis ? output.height-y-1 : y;
        shape.scanline(scanline, projection.unprojectY(y+.5));
        for (int x = 0; x < output.width; ++x)
            *output(x, row) = (float) scanline.filled(projection.unprojectX(x+.5), fillRule);
    }
}

void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule) {
    Scanline scanline;
    for (int y = 0; y < sdf.height; ++y) {
        int row = shape.inverseYAxis ? sdf.height-y-1 : y;
        shape.scanline(scanline, projection.unprojectY(y+.5));
        for (int x = 0; x < sdf.width; ++x) {
            bool fill = scanline.filled(projection.unprojectX(x+.5), fillRule);
            float &sd = *sdf(x, row);
            if ((sd > .5f) != fill)
                sd = 1.f-sd;
        }
    }
}

template <int N>
static void multiDistanceSignCorrection(const BitmapRef<float, N> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule) {
    int w = sdf.width, h = sdf.height;
    if (!(w*h))
        return;
    Scanline scanline;
    bool ambiguous = false;
    std::vector<char> matchMap;
    matchMap.resize(w*h);
    char *match = &matchMap[0];
    for (int y = 0; y < h; ++y) {
        int row = shape.inverseYAxis ? h-y-1 : y;
        shape.scanline(scanline, projection.unprojectY(y+.5));
        for (int x = 0; x < w; ++x) {
            bool fill = scanline.filled(projection.unprojectX(x+.5), fillRule);
            float *msd = sdf(x, row);
            float sd = median(msd[0], msd[1], msd[2]);
            if (sd == .5f)
                ambiguous = true;
            else if ((sd > .5f) != fill) {
                msd[0] = 1.f-msd[0];
                msd[1] = 1.f-msd[1];
                msd[2] = 1.f-msd[2];
                *match = -1;
            } else
                *match = 1;
            if (N >= 4 && (msd[3] > .5f) != fill)
                msd[3] = 1.f-msd[3];
            ++match;
        }
    }
    // This step is necessary to avoid artifacts when whole shape is inverted
    if (ambiguous) {
        match = &matchMap[0];
        for (int y = 0; y < h; ++y) {
            int row = shape.inverseYAxis ? h-y-1 : y;
            for (int x = 0; x < w; ++x) {
                if (!*match) {
                    int neighborMatch = 0;
                    if (x > 0) neighborMatch += *(match-1);
                    if (x < w-1) neighborMatch += *(match+1);
                    if (y > 0) neighborMatch += *(match-w);
                    if (y < h-1) neighborMatch += *(match+w);
                    if (neighborMatch < 0) {
                        float *msd = sdf(x, row);
                        msd[0] = 1.f-msd[0];
                        msd[1] = 1.f-msd[1];
                        msd[2] = 1.f-msd[2];
                    }
                }
                ++match;
            }
        }
    }
}

void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule) {
    multiDistanceSignCorrection(sdf, shape, projection, fillRule);
}

void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule) {
    multiDistanceSignCorrection(sdf, shape, projection, fillRule);
}

// Legacy API

void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule) {
    rasterize(output, shape, Projection(scale, translate), fillRule);
}

void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule) {
    distanceSignCorrection(sdf, shape, Projection(scale, translate), fillRule);
}

void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule) {
    distanceSignCorrection(sdf, shape, Projection(scale, translate), fillRule);
}

void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Vector2 &scale, const Vector2 &translate, FillRule fillRule) {
    distanceSignCorrection(sdf, shape, Projection(scale, translate), fillRule);
}

}
