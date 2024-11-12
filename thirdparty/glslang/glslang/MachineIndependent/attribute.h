/**************************************************************************/
/*  attribute.h                                                           */
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

//
// Copyright (C) 2017 LunarG, Inc.
// Copyright (C) 2018 Google, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef _ATTRIBUTE_INCLUDED_
#define _ATTRIBUTE_INCLUDED_

#include "../Include/Common.h"
#include "../Include/ConstantUnion.h"

namespace glslang {

    enum TAttributeType {
        EatNone,
        EatAllow_uav_condition,
        EatBranch,
        EatCall,
        EatDomain,
        EatEarlyDepthStencil,
        EatFastOpt,
        EatFlatten,
        EatForceCase,
        EatInstance,
        EatMaxTessFactor,
        EatNumThreads,
        EatMaxVertexCount,
        EatOutputControlPoints,
        EatOutputTopology,
        EatPartitioning,
        EatPatchConstantFunc,
        EatPatchSize,
        EatUnroll,
        EatLoop,
        EatBinding,
        EatGlobalBinding,
        EatLocation,
        EatInputAttachment,
        EatBuiltIn,
        EatPushConstant,
        EatConstantId,
        EatDependencyInfinite,
        EatDependencyLength,
        EatMinIterations,
        EatMaxIterations,
        EatIterationMultiple,
        EatPeelCount,
        EatPartialCount,
        EatFormatRgba32f,
        EatFormatRgba16f,
        EatFormatR32f,
        EatFormatRgba8,
        EatFormatRgba8Snorm,
        EatFormatRg32f,
        EatFormatRg16f,
        EatFormatR11fG11fB10f,
        EatFormatR16f,
        EatFormatRgba16,
        EatFormatRgb10A2,
        EatFormatRg16,
        EatFormatRg8,
        EatFormatR16,
        EatFormatR8,
        EatFormatRgba16Snorm,
        EatFormatRg16Snorm,
        EatFormatRg8Snorm,
        EatFormatR16Snorm,
        EatFormatR8Snorm,
        EatFormatRgba32i,
        EatFormatRgba16i,
        EatFormatRgba8i,
        EatFormatR32i,
        EatFormatRg32i,
        EatFormatRg16i,
        EatFormatRg8i,
        EatFormatR16i,
        EatFormatR8i,
        EatFormatRgba32ui,
        EatFormatRgba16ui,
        EatFormatRgba8ui,
        EatFormatR32ui,
        EatFormatRgb10a2ui,
        EatFormatRg32ui,
        EatFormatRg16ui,
        EatFormatRg8ui,
        EatFormatR16ui,
        EatFormatR8ui,
        EatFormatUnknown,
        EatNonWritable,
        EatNonReadable,
        EatSubgroupUniformControlFlow,
        EatExport,
        EatMaximallyReconverges,
    };

    class TIntermAggregate;

    struct TAttributeArgs {
        TAttributeType name;
        const TIntermAggregate* args;

        // Obtain attribute as integer
        // Return false if it cannot be obtained
        bool getInt(int& value, int argNum = 0) const;

        // Obtain attribute as string, with optional to-lower transform
        // Return false if it cannot be obtained
        bool getString(TString& value, int argNum = 0, bool convertToLower = true) const;

        // How many arguments were provided to the attribute?
        int size() const;

    protected:
        const TConstUnion* getConstUnion(TBasicType basicType, int argNum) const;
    };

    typedef TList<TAttributeArgs> TAttributes;

} // end namespace glslang

#endif // _ATTRIBUTE_INCLUDED_
