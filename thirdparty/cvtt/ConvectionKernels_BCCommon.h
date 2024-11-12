/**************************************************************************/
/*  ConvectionKernels_BCCommon.h                                          */
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
#ifndef __CVTT_BCCOMMON_H__
#define __CVTT_BCCOMMON_H__

#include "ConvectionKernels_AggregatedError.h"
#include "ConvectionKernels_ParallelMath.h"

namespace cvtt
{
    namespace Internal
    {
        class BCCommon
        {
        public:
            typedef ParallelMath::Float MFloat;
            typedef ParallelMath::UInt16 MUInt16;
            typedef ParallelMath::UInt15 MUInt15;
            typedef ParallelMath::AInt16 MAInt16;
            typedef ParallelMath::SInt16 MSInt16;
            typedef ParallelMath::SInt32 MSInt32;

            static int TweakRoundsForRange(int range);

            template<int TVectorSize>
            static void ComputeErrorLDR(uint32_t flags, const MUInt15 reconstructed[TVectorSize], const MUInt15 original[TVectorSize], int numRealChannels, AggregatedError<TVectorSize> &aggError)
            {
                for (int ch = 0; ch < numRealChannels; ch++)
                    aggError.Add(ParallelMath::SqDiffUInt8(reconstructed[ch], original[ch]), ch);
            }

            template<int TVectorSize>
            static void ComputeErrorLDR(uint32_t flags, const MUInt15 reconstructed[TVectorSize], const MUInt15 original[TVectorSize], AggregatedError<TVectorSize> &aggError)
            {
                ComputeErrorLDR<TVectorSize>(flags, reconstructed, original, TVectorSize, aggError);
            }

            template<int TVectorSize>
            static MFloat ComputeErrorLDRSimple(uint32_t flags, const MUInt15 reconstructed[TVectorSize], const MUInt15 original[TVectorSize], int numRealChannels, const float *channelWeightsSq)
            {
                AggregatedError<TVectorSize> aggError;
                ComputeErrorLDR<TVectorSize>(flags, reconstructed, original, numRealChannels, aggError);
                return aggError.Finalize(flags, channelWeightsSq);
            }

            template<int TVectorSize>
            static MFloat ComputeErrorHDRFast(uint32_t flags, const MSInt16 reconstructed[TVectorSize], const MSInt16 original[TVectorSize], const float channelWeightsSq[TVectorSize])
            {
                MFloat error = ParallelMath::MakeFloatZero();
                if (flags & Flags::Uniform)
                {
                    for (int ch = 0; ch < TVectorSize; ch++)
                        error = error + ParallelMath::SqDiffSInt16(reconstructed[ch], original[ch]);
                }
                else
                {
                    for (int ch = 0; ch < TVectorSize; ch++)
                        error = error + ParallelMath::SqDiffSInt16(reconstructed[ch], original[ch]) * ParallelMath::MakeFloat(channelWeightsSq[ch]);
                }

                return error;
            }

            template<int TVectorSize>
            static MFloat ComputeErrorHDRSlow(uint32_t flags, const MSInt16 reconstructed[TVectorSize], const MSInt16 original[TVectorSize], const float channelWeightsSq[TVectorSize])
            {
                MFloat error = ParallelMath::MakeFloatZero();
                if (flags & Flags::Uniform)
                {
                    for (int ch = 0; ch < TVectorSize; ch++)
                        error = error + ParallelMath::SqDiff2CL(reconstructed[ch], original[ch]);
                }
                else
                {
                    for (int ch = 0; ch < TVectorSize; ch++)
                        error = error + ParallelMath::SqDiff2CL(reconstructed[ch], original[ch]) * ParallelMath::MakeFloat(channelWeightsSq[ch]);
                }

                return error;
            }

            template<int TChannelCount>
            static void PreWeightPixelsLDR(MFloat preWeightedPixels[16][TChannelCount], const MUInt15 pixels[16][TChannelCount], const float channelWeights[TChannelCount])
            {
                for (int px = 0; px < 16; px++)
                {
                    for (int ch = 0; ch < TChannelCount; ch++)
                        preWeightedPixels[px][ch] = ParallelMath::ToFloat(pixels[px][ch]) * channelWeights[ch];
                }
            }

            template<int TChannelCount>
            static void PreWeightPixelsHDR(MFloat preWeightedPixels[16][TChannelCount], const MSInt16 pixels[16][TChannelCount], const float channelWeights[TChannelCount])
            {
                for (int px = 0; px < 16; px++)
                {
                    for (int ch = 0; ch < TChannelCount; ch++)
                        preWeightedPixels[px][ch] = ParallelMath::ToFloat(pixels[px][ch]) * channelWeights[ch];
                }
            }
        };
    }
}

#endif
