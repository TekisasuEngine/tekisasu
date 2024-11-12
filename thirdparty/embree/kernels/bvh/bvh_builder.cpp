/**************************************************************************/
/*  bvh_builder.cpp                                                       */
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

// Copyright 2009-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "bvh_builder.h"

namespace embree
{
  namespace isa
  {
    template<int N>
    typename BVHN<N>::NodeRef BVHNBuilderVirtual<N>::BVHNBuilderV::build(FastAllocator* allocator, BuildProgressMonitor& progressFunc, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings)
    {
      auto createLeafFunc = [&] (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) -> NodeRef {
        return createLeaf(prims,set,alloc);
      };
      
      settings.branchingFactor = N;
      settings.maxDepth = BVH::maxBuildDepthLeaf;
      return BVHBuilderBinnedSAH::build<NodeRef>
        (FastAllocator::Create(allocator),typename BVH::AABBNode::Create2(),typename BVH::AABBNode::Set3(allocator,prims),createLeafFunc,progressFunc,prims,pinfo,settings);
    }


    template<int N>
    typename BVHN<N>::NodeRef BVHNBuilderQuantizedVirtual<N>::BVHNBuilderV::build(FastAllocator* allocator, BuildProgressMonitor& progressFunc, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings)
    {
      auto createLeafFunc = [&] (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) -> NodeRef {
        return createLeaf(prims,set,alloc);
      };
            
      settings.branchingFactor = N;
      settings.maxDepth = BVH::maxBuildDepthLeaf;
      return BVHBuilderBinnedSAH::build<NodeRef>
        (FastAllocator::Create(allocator),typename BVH::QuantizedNode::Create2(),typename BVH::QuantizedNode::Set2(),createLeafFunc,progressFunc,prims,pinfo,settings);
    }

    template<int N>
    typename BVHN<N>::NodeRecordMB BVHNBuilderMblurVirtual<N>::BVHNBuilderV::build(FastAllocator* allocator, BuildProgressMonitor& progressFunc, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings, const BBox1f& timeRange)
    {
      auto createLeafFunc = [&] (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) -> NodeRecordMB {
        return createLeaf(prims,set,alloc);
      };

      settings.branchingFactor = N;
      settings.maxDepth = BVH::maxBuildDepthLeaf;
      return BVHBuilderBinnedSAH::build<NodeRecordMB>
        (FastAllocator::Create(allocator),typename BVH::AABBNodeMB::Create(),typename BVH::AABBNodeMB::SetTimeRange(timeRange),createLeafFunc,progressFunc,prims,pinfo,settings);
    }

    template struct BVHNBuilderVirtual<4>;
    template struct BVHNBuilderQuantizedVirtual<4>;
    template struct BVHNBuilderMblurVirtual<4>;    

#if defined(__AVX__)
    template struct BVHNBuilderVirtual<8>;
    template struct BVHNBuilderQuantizedVirtual<8>;
    template struct BVHNBuilderMblurVirtual<8>;
#endif
  }
}
