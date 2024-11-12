/**************************************************************************/
/*  d3dx12_barriers.h                                                     */
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

#ifndef __D3DX12_BARRIERS_H__
#define __D3DX12_BARRIERS_H__

#if defined( __cplusplus )

#include "d3d12.h"

//------------------------------------------------------------------------------------------------
struct CD3DX12_RESOURCE_BARRIER : public D3D12_RESOURCE_BARRIER
{
    CD3DX12_RESOURCE_BARRIER() = default;
    explicit CD3DX12_RESOURCE_BARRIER(const D3D12_RESOURCE_BARRIER &o) noexcept :
        D3D12_RESOURCE_BARRIER(o)
    {}
    static inline CD3DX12_RESOURCE_BARRIER Transition(
        _In_ ID3D12Resource* pResource,
        D3D12_RESOURCE_STATES stateBefore,
        D3D12_RESOURCE_STATES stateAfter,
        UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        D3D12_RESOURCE_BARRIER_FLAGS flags = D3D12_RESOURCE_BARRIER_FLAG_NONE) noexcept
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        D3D12_RESOURCE_BARRIER &barrier = result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        result.Flags = flags;
        barrier.Transition.pResource = pResource;
        barrier.Transition.StateBefore = stateBefore;
        barrier.Transition.StateAfter = stateAfter;
        barrier.Transition.Subresource = subresource;
        return result;
    }
    static inline CD3DX12_RESOURCE_BARRIER Aliasing(
        _In_opt_ ID3D12Resource* pResourceBefore,
        _In_opt_ ID3D12Resource* pResourceAfter) noexcept
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        D3D12_RESOURCE_BARRIER &barrier = result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_ALIASING;
        barrier.Aliasing.pResourceBefore = pResourceBefore;
        barrier.Aliasing.pResourceAfter = pResourceAfter;
        return result;
    }
    static inline CD3DX12_RESOURCE_BARRIER UAV(
        _In_opt_ ID3D12Resource* pResource) noexcept
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        D3D12_RESOURCE_BARRIER &barrier = result;
        result.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
        barrier.UAV.pResource = pResource;
        return result;
    }
};

#if defined(D3D12_SDK_VERSION) && (D3D12_SDK_VERSION >= 608)

//================================================================================================
// D3DX12 Enhanced Barrier Helpers
//================================================================================================

class CD3DX12_BARRIER_SUBRESOURCE_RANGE : public D3D12_BARRIER_SUBRESOURCE_RANGE
{
public:
    CD3DX12_BARRIER_SUBRESOURCE_RANGE() = default;
    CD3DX12_BARRIER_SUBRESOURCE_RANGE(const D3D12_BARRIER_SUBRESOURCE_RANGE &o) noexcept :
        D3D12_BARRIER_SUBRESOURCE_RANGE(o)
    {}
    explicit CD3DX12_BARRIER_SUBRESOURCE_RANGE(UINT Subresource) noexcept :
        D3D12_BARRIER_SUBRESOURCE_RANGE{ Subresource, 0, 0, 0, 0, 0 }
    {}
    CD3DX12_BARRIER_SUBRESOURCE_RANGE(
        UINT firstMipLevel,
        UINT numMips,
        UINT firstArraySlice,
        UINT numArraySlices,
        UINT firstPlane = 0,
        UINT numPlanes = 1) noexcept :
        D3D12_BARRIER_SUBRESOURCE_RANGE
        {
            firstMipLevel,
            numMips,
            firstArraySlice,
            numArraySlices,
            firstPlane,
            numPlanes
        }
    {}
};

class CD3DX12_GLOBAL_BARRIER : public D3D12_GLOBAL_BARRIER
{
public:
    CD3DX12_GLOBAL_BARRIER() = default;
    CD3DX12_GLOBAL_BARRIER(const D3D12_GLOBAL_BARRIER &o) noexcept : D3D12_GLOBAL_BARRIER(o){}
    CD3DX12_GLOBAL_BARRIER(
        D3D12_BARRIER_SYNC syncBefore,
        D3D12_BARRIER_SYNC syncAfter,
        D3D12_BARRIER_ACCESS accessBefore,
        D3D12_BARRIER_ACCESS accessAfter) noexcept : D3D12_GLOBAL_BARRIER {
            syncBefore,
            syncAfter,
            accessBefore,
            accessAfter
        }
    {}
};

class CD3DX12_BUFFER_BARRIER : public D3D12_BUFFER_BARRIER
{
public:
    CD3DX12_BUFFER_BARRIER() = default;
    CD3DX12_BUFFER_BARRIER(const D3D12_BUFFER_BARRIER &o) noexcept : D3D12_BUFFER_BARRIER(o){}
    CD3DX12_BUFFER_BARRIER(
        D3D12_BARRIER_SYNC syncBefore,
        D3D12_BARRIER_SYNC syncAfter,
        D3D12_BARRIER_ACCESS accessBefore,
        D3D12_BARRIER_ACCESS accessAfter,
        ID3D12Resource *pRes) noexcept : D3D12_BUFFER_BARRIER {
            syncBefore,
            syncAfter,
            accessBefore,
            accessAfter,
            pRes,
            0, ULLONG_MAX
        }
    {}
};

class CD3DX12_TEXTURE_BARRIER : public D3D12_TEXTURE_BARRIER
{
public:
    CD3DX12_TEXTURE_BARRIER() = default;
    CD3DX12_TEXTURE_BARRIER(const D3D12_TEXTURE_BARRIER &o) noexcept : D3D12_TEXTURE_BARRIER(o){}
    CD3DX12_TEXTURE_BARRIER(
        D3D12_BARRIER_SYNC syncBefore,
        D3D12_BARRIER_SYNC syncAfter,
        D3D12_BARRIER_ACCESS accessBefore,
        D3D12_BARRIER_ACCESS accessAfter,
        D3D12_BARRIER_LAYOUT layoutBefore,
        D3D12_BARRIER_LAYOUT layoutAfter,
        ID3D12Resource *pRes,
        const D3D12_BARRIER_SUBRESOURCE_RANGE &subresources,
        D3D12_TEXTURE_BARRIER_FLAGS flag = D3D12_TEXTURE_BARRIER_FLAG_NONE) noexcept : D3D12_TEXTURE_BARRIER {
            syncBefore,
            syncAfter,
            accessBefore,
            accessAfter,
            layoutBefore,
            layoutAfter,
            pRes,
            subresources,
            flag
        }
    {}
};

class CD3DX12_BARRIER_GROUP : public D3D12_BARRIER_GROUP
{
public:
    CD3DX12_BARRIER_GROUP() = default;
    CD3DX12_BARRIER_GROUP(const D3D12_BARRIER_GROUP &o) noexcept : D3D12_BARRIER_GROUP(o){}
    CD3DX12_BARRIER_GROUP(UINT32 numBarriers, const D3D12_BUFFER_BARRIER *pBarriers) noexcept
    {
        Type = D3D12_BARRIER_TYPE_BUFFER;
        NumBarriers = numBarriers;
        pBufferBarriers = pBarriers;
    }
    CD3DX12_BARRIER_GROUP(UINT32 numBarriers, const D3D12_TEXTURE_BARRIER *pBarriers) noexcept
    {
        Type = D3D12_BARRIER_TYPE_TEXTURE;
        NumBarriers = numBarriers;
        pTextureBarriers = pBarriers;
    }
    CD3DX12_BARRIER_GROUP(UINT32 numBarriers, const D3D12_GLOBAL_BARRIER *pBarriers) noexcept
    {
        Type = D3D12_BARRIER_TYPE_GLOBAL;
        NumBarriers = numBarriers;
        pGlobalBarriers = pBarriers;
    }
};
#endif // D3D12_SDK_VERSION >= 608


#endif // defined( __cplusplus )

#endif // __D3DX12_BARRIERS_H__
