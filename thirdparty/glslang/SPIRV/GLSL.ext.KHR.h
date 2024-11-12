/**************************************************************************/
/*  GLSL.ext.KHR.h                                                        */
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

/*
** Copyright (c) 2014-2020 The Khronos Group Inc.
** Copyright (C) 2022-2024 Arm Limited.
** Modifications Copyright (C) 2020 Advanced Micro Devices, Inc. All rights reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and/or associated documentation files (the "Materials"),
** to deal in the Materials without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Materials, and to permit persons to whom the
** Materials are furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Materials.
**
** MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS KHRONOS
** STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS SPECIFICATIONS AND
** HEADER INFORMATION ARE LOCATED AT https://www.khronos.org/registry/
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
** IN THE MATERIALS.
*/

#ifndef GLSLextKHR_H
#define GLSLextKHR_H

static const int GLSLextKHRVersion = 100;
static const int GLSLextKHRRevision = 3;

static const char* const E_SPV_KHR_shader_ballot                = "SPV_KHR_shader_ballot";
static const char* const E_SPV_KHR_subgroup_vote                = "SPV_KHR_subgroup_vote";
static const char* const E_SPV_KHR_device_group                 = "SPV_KHR_device_group";
static const char* const E_SPV_KHR_multiview                    = "SPV_KHR_multiview";
static const char* const E_SPV_KHR_shader_draw_parameters       = "SPV_KHR_shader_draw_parameters";
static const char* const E_SPV_KHR_16bit_storage                = "SPV_KHR_16bit_storage";
static const char* const E_SPV_KHR_8bit_storage                 = "SPV_KHR_8bit_storage";
static const char* const E_SPV_KHR_storage_buffer_storage_class = "SPV_KHR_storage_buffer_storage_class";
static const char* const E_SPV_KHR_post_depth_coverage          = "SPV_KHR_post_depth_coverage";
static const char* const E_SPV_KHR_vulkan_memory_model          = "SPV_KHR_vulkan_memory_model";
static const char* const E_SPV_EXT_physical_storage_buffer      = "SPV_EXT_physical_storage_buffer";
static const char* const E_SPV_KHR_physical_storage_buffer      = "SPV_KHR_physical_storage_buffer";
static const char* const E_SPV_EXT_fragment_shader_interlock    = "SPV_EXT_fragment_shader_interlock";
static const char* const E_SPV_KHR_shader_clock                 = "SPV_KHR_shader_clock";
static const char* const E_SPV_KHR_non_semantic_info            = "SPV_KHR_non_semantic_info";
static const char* const E_SPV_KHR_ray_tracing                  = "SPV_KHR_ray_tracing";
static const char* const E_SPV_KHR_ray_query                    = "SPV_KHR_ray_query";
static const char* const E_SPV_KHR_fragment_shading_rate        = "SPV_KHR_fragment_shading_rate";
static const char* const E_SPV_KHR_terminate_invocation         = "SPV_KHR_terminate_invocation";
static const char* const E_SPV_KHR_workgroup_memory_explicit_layout = "SPV_KHR_workgroup_memory_explicit_layout";
static const char* const E_SPV_KHR_subgroup_uniform_control_flow = "SPV_KHR_subgroup_uniform_control_flow";
static const char* const E_SPV_KHR_fragment_shader_barycentric = "SPV_KHR_fragment_shader_barycentric";
static const char* const E_SPV_KHR_quad_control                = "SPV_KHR_quad_control";
static const char* const E_SPV_AMD_shader_early_and_late_fragment_tests = "SPV_AMD_shader_early_and_late_fragment_tests";
static const char* const E_SPV_KHR_ray_tracing_position_fetch   = "SPV_KHR_ray_tracing_position_fetch";
static const char* const E_SPV_KHR_cooperative_matrix           = "SPV_KHR_cooperative_matrix";
static const char* const E_SPV_KHR_maximal_reconvergence        = "SPV_KHR_maximal_reconvergence";
static const char* const E_SPV_KHR_subgroup_rotate              = "SPV_KHR_subgroup_rotate";
static const char* const E_SPV_KHR_expect_assume                = "SPV_KHR_expect_assume";

#endif  // #ifndef GLSLextKHR_H
