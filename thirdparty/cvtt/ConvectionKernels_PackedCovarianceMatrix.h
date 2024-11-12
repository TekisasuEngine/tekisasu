/**************************************************************************/
/*  ConvectionKernels_PackedCovarianceMatrix.h                            */
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
#ifndef __CVTT_COVARIANCEMATRIX_H__
#define __CVTT_COVARIANCEMATRIX_H__

namespace cvtt
{
    namespace Internal
    {

        template<int TMatrixSize>
        class PackedCovarianceMatrix
        {
        public:
            // 0: xx,
            // 1: xy, yy
            // 3: xz, yz, zz 
            // 6: xw, yw, zw, ww
            // ... etc.
            static const int PyramidSize = (TMatrixSize * (TMatrixSize + 1)) / 2;

            typedef ParallelMath::Float MFloat;

            PackedCovarianceMatrix()
            {
                for (int i = 0; i < PyramidSize; i++)
                    m_values[i] = ParallelMath::MakeFloatZero();
            }

            void Add(const ParallelMath::Float *vec, const ParallelMath::Float &weight)
            {
                int index = 0;
                for (int row = 0; row < TMatrixSize; row++)
                {
                    for (int col = 0; col <= row; col++)
                    {
                        m_values[index] = m_values[index] + vec[row] * vec[col] * weight;
                        index++;
                    }
                }
            }

            void Product(MFloat *outVec, const MFloat *inVec)
            {
                for (int row = 0; row < TMatrixSize; row++)
                {
                    MFloat sum = ParallelMath::MakeFloatZero();

                    int index = (row * (row + 1)) >> 1;
                    for (int col = 0; col < TMatrixSize; col++)
                    {
                        sum = sum + inVec[col] * m_values[index];
                        if (col >= row)
                            index += col + 1;
                        else
                            index++;
                    }

                    outVec[row] = sum;
                }
            }

        private:
            ParallelMath::Float m_values[PyramidSize];
        };
    }
}

#endif
