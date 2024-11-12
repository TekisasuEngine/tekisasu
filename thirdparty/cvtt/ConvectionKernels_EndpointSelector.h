/**************************************************************************/
/*  ConvectionKernels_EndpointSelector.h                                  */
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
#ifndef __CVTT_ENDPOINTSELECTOR_H__
#define __CVTT_ENDPOINTSELECTOR_H__

#include "ConvectionKernels_ParallelMath.h"
#include "ConvectionKernels_UnfinishedEndpoints.h"
#include "ConvectionKernels_PackedCovarianceMatrix.h"

namespace cvtt
{
    namespace Internal
    {
        static const int NumEndpointSelectorPasses = 3;

        template<int TVectorSize, int TIterationCount>
        class EndpointSelector
        {
        public:
            typedef ParallelMath::Float MFloat;

            EndpointSelector()
            {
                for (int ch = 0; ch < TVectorSize; ch++)
                {
                    m_centroid[ch] = ParallelMath::MakeFloatZero();
                    m_direction[ch] = ParallelMath::MakeFloatZero();
                }
                m_weightTotal = ParallelMath::MakeFloatZero();
                m_minDist = ParallelMath::MakeFloat(FLT_MAX);
                m_maxDist = ParallelMath::MakeFloat(-FLT_MAX);
            }

            void ContributePass(const MFloat *value, int pass, const MFloat &weight)
            {
                if (pass == 0)
                    ContributeCentroid(value, weight);
                else if (pass == 1)
                    ContributeDirection(value, weight);
                else if (pass == 2)
                    ContributeMinMax(value);
            }

            void FinishPass(int pass)
            {
                if (pass == 0)
                    FinishCentroid();
                else if (pass == 1)
                    FinishDirection();
            }

            UnfinishedEndpoints<TVectorSize> GetEndpoints(const float channelWeights[TVectorSize]) const
            {
                MFloat unweightedBase[TVectorSize];
                MFloat unweightedOffset[TVectorSize];

                for (int ch = 0; ch < TVectorSize; ch++)
                {
                    MFloat min = m_centroid[ch] + m_direction[ch] * m_minDist;
                    MFloat max = m_centroid[ch] + m_direction[ch] * m_maxDist;

                    float safeWeight = channelWeights[ch];
                    if (safeWeight == 0.f)
                        safeWeight = 1.0f;

                    unweightedBase[ch] = min / channelWeights[ch];
                    unweightedOffset[ch] = (max - min) / channelWeights[ch];
                }

                return UnfinishedEndpoints<TVectorSize>(unweightedBase, unweightedOffset);
            }

        private:
            void ContributeCentroid(const MFloat *value, const MFloat &weight)
            {
                for (int ch = 0; ch < TVectorSize; ch++)
                    m_centroid[ch] = m_centroid[ch] + value[ch] * weight;
                m_weightTotal = m_weightTotal + weight;
            }

            void FinishCentroid()
            {
                MFloat denom = m_weightTotal;
                ParallelMath::MakeSafeDenominator(denom);

                for (int ch = 0; ch < TVectorSize; ch++)
                    m_centroid[ch] = m_centroid[ch] / denom;
            }

            void ContributeDirection(const MFloat *value, const MFloat &weight)
            {
                MFloat diff[TVectorSize];
                for (int ch = 0; ch < TVectorSize; ch++)
                    diff[ch] = value[ch] - m_centroid[ch];

                m_covarianceMatrix.Add(diff, weight);
            }

            void FinishDirection()
            {
                MFloat approx[TVectorSize];
                for (int ch = 0; ch < TVectorSize; ch++)
                    approx[ch] = ParallelMath::MakeFloat(1.0f);

                for (int i = 0; i < TIterationCount; i++)
                {
                    MFloat product[TVectorSize];
                    m_covarianceMatrix.Product(product, approx);

                    MFloat largestComponent = product[0];
                    for (int ch = 1; ch < TVectorSize; ch++)
                        largestComponent = ParallelMath::Max(largestComponent, product[ch]);

                    // product = largestComponent*newApprox
                    ParallelMath::MakeSafeDenominator(largestComponent);
                    for (int ch = 0; ch < TVectorSize; ch++)
                        approx[ch] = product[ch] / largestComponent;
                }

                // Normalize
                MFloat approxLen = ParallelMath::MakeFloatZero();
                for (int ch = 0; ch < TVectorSize; ch++)
                    approxLen = approxLen + approx[ch] * approx[ch];

                approxLen = ParallelMath::Sqrt(approxLen);

                ParallelMath::MakeSafeDenominator(approxLen);

                for (int ch = 0; ch < TVectorSize; ch++)
                    m_direction[ch] = approx[ch] / approxLen;
            }

            void ContributeMinMax(const MFloat *value)
            {
                MFloat dist = ParallelMath::MakeFloatZero();
                for (int ch = 0; ch < TVectorSize; ch++)
                    dist = dist + m_direction[ch] * (value[ch] - m_centroid[ch]);

                m_minDist = ParallelMath::Min(m_minDist, dist);
                m_maxDist = ParallelMath::Max(m_maxDist, dist);
            }

            ParallelMath::Float m_centroid[TVectorSize];
            ParallelMath::Float m_direction[TVectorSize];
            PackedCovarianceMatrix<TVectorSize> m_covarianceMatrix;
            ParallelMath::Float m_weightTotal;

            ParallelMath::Float m_minDist;
            ParallelMath::Float m_maxDist;
        };
    }
}

#endif
