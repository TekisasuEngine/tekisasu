/**************************************************************************/
/*  ConvectionKernels_S3TC.h                                              */
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
#ifndef __CVTT_S3TC_H__
#define __CVTT_S3TC_H__

#include "ConvectionKernels_ParallelMath.h"

namespace cvtt
{
    namespace Internal
    {
        template<int TVectorSize>
        class EndpointRefiner;
    }

    struct PixelBlockU8;
}

namespace cvtt
{
    namespace Internal
    {
        class S3TCComputer
        {
        public:
            typedef ParallelMath::Float MFloat;
            typedef ParallelMath::SInt16 MSInt16;
            typedef ParallelMath::UInt15 MUInt15;
            typedef ParallelMath::UInt16 MUInt16;
            typedef ParallelMath::SInt32 MSInt32;

            static void Init(MFloat& error);
            static void QuantizeTo6Bits(MUInt15& v);
            static void QuantizeTo5Bits(MUInt15& v);
            static void QuantizeTo565(MUInt15 endPoint[3]);
            static MFloat ParanoidFactorForSpan(const MSInt16& span);
            static MFloat ParanoidDiff(const MUInt15& a, const MUInt15& b, const MFloat& d);
            static void TestSingleColor(uint32_t flags, const MUInt15 pixels[16][4], const MFloat floatPixels[16][4], int range, const float* channelWeights,
                MFloat &bestError, MUInt15 bestEndpoints[2][3], MUInt15 bestIndexes[16], MUInt15 &bestRange, const ParallelMath::RoundTowardNearestForScope *rtn);
            static void TestEndpoints(uint32_t flags, const MUInt15 pixels[16][4], const MFloat floatPixels[16][4], const MFloat preWeightedPixels[16][4], const MUInt15 unquantizedEndPoints[2][3], int range, const float* channelWeights,
                MFloat &bestError, MUInt15 bestEndpoints[2][3], MUInt15 bestIndexes[16], MUInt15 &bestRange, EndpointRefiner<3> *refiner, const ParallelMath::RoundTowardNearestForScope *rtn);
            static void TestCounts(uint32_t flags, const int *counts, int nCounts, const MUInt15 &numElements, const MUInt15 pixels[16][4], const MFloat floatPixels[16][4], const MFloat preWeightedPixels[16][4], bool alphaTest,
                const MFloat floatSortedInputs[16][4], const MFloat preWeightedFloatSortedInputs[16][4], const float *channelWeights, MFloat &bestError, MUInt15 bestEndpoints[2][3], MUInt15 bestIndexes[16], MUInt15 &bestRange,
                const ParallelMath::RoundTowardNearestForScope* rtn);
            static void PackExplicitAlpha(uint32_t flags, const PixelBlockU8* inputs, int inputChannel, uint8_t* packedBlocks, size_t packedBlockStride);
            static void PackInterpolatedAlpha(uint32_t flags, const PixelBlockU8* inputs, int inputChannel, uint8_t* packedBlocks, size_t packedBlockStride, bool isSigned, int maxTweakRounds, int numRefineRounds);
            static void PackRGB(uint32_t flags, const PixelBlockU8* inputs, uint8_t* packedBlocks, size_t packedBlockStride, const float channelWeights[4], bool alphaTest, float alphaThreshold, bool exhaustive, int maxTweakRounds, int numRefineRounds);
        };
    }
}

#endif
