/**************************************************************************/
/*  d3dx12_render_pass.h                                                  */
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

//*********************************************************
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//
//*********************************************************

#pragma once

#ifndef __cplusplus
#error D3DX12 requires C++
#endif

#include "d3d12.h"
#if defined(D3D12_SDK_VERSION) && (D3D12_SDK_VERSION >= 609)
inline bool operator==(const D3D12_RENDER_PASS_BEGINNING_ACCESS_PRESERVE_LOCAL_PARAMETERS& a, const D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS& b) noexcept
{
    return ((a.AdditionalWidth == b.AdditionalWidth) && (a.AdditionalHeight == b.AdditionalHeight));
}

inline bool operator==(const D3D12_RENDER_PASS_BEGINNING_ACCESS_PRESERVE_LOCAL_PARAMETERS& a, const D3D12_RENDER_PASS_BEGINNING_ACCESS_PRESERVE_LOCAL_PARAMETERS& b) noexcept
{
    return ((a.AdditionalWidth == b.AdditionalWidth) && (a.AdditionalHeight == b.AdditionalHeight));
}

inline bool operator==(const D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS& a, const D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS& b) noexcept
{
    return ((a.AdditionalWidth == b.AdditionalWidth) && (a.AdditionalHeight == b.AdditionalHeight));
}
#endif

inline bool operator==( const D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS &a, const D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS &b) noexcept
{
    return a.ClearValue == b.ClearValue;
}

inline bool operator==( const D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS &a, const D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS &b) noexcept
{
    if (a.pSrcResource != b.pSrcResource) return false;
    if (a.pDstResource != b.pDstResource) return false;
    if (a.SubresourceCount != b.SubresourceCount) return false;
    if (a.Format != b.Format) return false;
    if (a.ResolveMode != b.ResolveMode) return false;
    if (a.PreserveResolveSource != b.PreserveResolveSource) return false;
    return true;
}

inline bool operator==( const D3D12_RENDER_PASS_BEGINNING_ACCESS &a, const D3D12_RENDER_PASS_BEGINNING_ACCESS &b) noexcept
{
    if (a.Type != b.Type) return false;
    switch (a.Type)
    {
    case D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR:
        if (!(a.Clear == b.Clear)) return false;
        break;
#if defined(D3D12_SDK_VERSION) && (D3D12_SDK_VERSION >= 609)
    case D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_RENDER:
    case D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_SRV:
    case D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_UAV:
        if (!(a.PreserveLocal == b.PreserveLocal)) return false;
        break;
#endif
    }
    return true;
}

inline bool operator==(const D3D12_RENDER_PASS_ENDING_ACCESS& a, const D3D12_RENDER_PASS_ENDING_ACCESS& b) noexcept
{
    if (a.Type != b.Type) return false;
    switch (a.Type)
    {
    case D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_RESOLVE:
        if (!(a.Resolve == b.Resolve)) return false;
        break;
#if defined(D3D12_SDK_VERSION) && (D3D12_SDK_VERSION >= 609)
    case D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_RENDER:
    case D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_SRV:
    case D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_UAV:
        if (!(a.PreserveLocal == b.PreserveLocal)) return false;
        break;
#endif
    }

    return true;
}

inline bool operator==( const D3D12_RENDER_PASS_RENDER_TARGET_DESC &a, const D3D12_RENDER_PASS_RENDER_TARGET_DESC &b) noexcept
{
    if (a.cpuDescriptor.ptr != b.cpuDescriptor.ptr) return false;
    if (!(a.BeginningAccess == b.BeginningAccess)) return false;
    if (!(a.EndingAccess == b.EndingAccess)) return false;
    return true;
}
inline bool operator==( const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC &a, const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC &b) noexcept
{
    if (a.cpuDescriptor.ptr != b.cpuDescriptor.ptr) return false;
    if (!(a.DepthBeginningAccess == b.DepthBeginningAccess)) return false;
    if (!(a.StencilBeginningAccess == b.StencilBeginningAccess)) return false;
    if (!(a.DepthEndingAccess == b.DepthEndingAccess)) return false;
    if (!(a.StencilEndingAccess == b.StencilEndingAccess)) return false;
    return true;
}
