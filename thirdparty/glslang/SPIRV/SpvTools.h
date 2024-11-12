/**************************************************************************/
/*  SpvTools.h                                                            */
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
// Copyright (C) 2014-2016 LunarG, Inc.
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
// Call into SPIRV-Tools to disassemble, validate, and optimize.
//

#pragma once
#ifndef GLSLANG_SPV_TOOLS_H
#define GLSLANG_SPV_TOOLS_H

#if ENABLE_OPT
#include <vector>
#include <ostream>
#include "spirv-tools/libspirv.h"
#endif

#include "glslang/MachineIndependent/localintermediate.h"
#include "GlslangToSpv.h"
#include "Logger.h"

namespace glslang {

#if ENABLE_OPT

// Translate glslang's view of target versioning to what SPIRV-Tools uses.
spv_target_env MapToSpirvToolsEnv(const SpvVersion& spvVersion, spv::SpvBuildLogger* logger);

// Use the SPIRV-Tools disassembler to print SPIR-V using a SPV_ENV_UNIVERSAL_1_3 environment.
void SpirvToolsDisassemble(std::ostream& out, const std::vector<unsigned int>& spirv);

// Use the SPIRV-Tools disassembler to print SPIR-V with a provided SPIR-V environment.
void SpirvToolsDisassemble(std::ostream& out, const std::vector<unsigned int>& spirv,
                           spv_target_env requested_context);

// Apply the SPIRV-Tools validator to generated SPIR-V.
void SpirvToolsValidate(const glslang::TIntermediate& intermediate, std::vector<unsigned int>& spirv,
                        spv::SpvBuildLogger*, bool prelegalization);

// Apply the SPIRV-Tools optimizer to generated SPIR-V.  HLSL SPIR-V is legalized in the process.
void SpirvToolsTransform(const glslang::TIntermediate& intermediate, std::vector<unsigned int>& spirv,
                         spv::SpvBuildLogger*, const SpvOptions*);

// Apply the SPIRV-Tools EliminateDeadInputComponents pass to generated SPIR-V. Put result in |spirv|.
void SpirvToolsEliminateDeadInputComponents(spv_target_env target_env, std::vector<unsigned int>& spirv,
                                            spv::SpvBuildLogger*);

// Apply the SPIRV-Tools AnalyzeDeadOutputStores pass to generated SPIR-V. Put result in |live_locs|.
// Return true if the result is valid.
bool SpirvToolsAnalyzeDeadOutputStores(spv_target_env target_env, std::vector<unsigned int>& spirv,
                                       std::unordered_set<uint32_t>* live_locs,
                                       std::unordered_set<uint32_t>* live_builtins, spv::SpvBuildLogger*);

// Apply the SPIRV-Tools EliminateDeadOutputStores and AggressiveDeadCodeElimination passes to generated SPIR-V using
// |live_locs|. Put result in |spirv|.
void SpirvToolsEliminateDeadOutputStores(spv_target_env target_env, std::vector<unsigned int>& spirv,
                                         std::unordered_set<uint32_t>* live_locs,
                                         std::unordered_set<uint32_t>* live_builtins, spv::SpvBuildLogger*);

// Apply the SPIRV-Tools optimizer to strip debug info from SPIR-V.  This is implicitly done by
// SpirvToolsTransform if spvOptions->stripDebugInfo is set, but can be called separately if
// optimization is disabled.
void SpirvToolsStripDebugInfo(const glslang::TIntermediate& intermediate,
        std::vector<unsigned int>& spirv, spv::SpvBuildLogger*);

#endif

} // end namespace glslang

#endif // GLSLANG_SPV_TOOLS_H
