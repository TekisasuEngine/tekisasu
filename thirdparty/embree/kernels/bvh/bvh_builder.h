/**************************************************************************/
/*  bvh_builder.h                                                         */
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

#include "bvh.h"
#include "../builders/bvh_builder_sah.h"
#include "../builders/bvh_builder_msmblur.h"

namespace embree
{
  namespace isa
  {
    /************************************************************************************/
    /************************************************************************************/
    /************************************************************************************/
    /************************************************************************************/

    template<int N>
      struct BVHNBuilderVirtual
      {
        typedef BVHN<N> BVH;
        typedef typename BVH::NodeRef NodeRef;
        typedef FastAllocator::CachedAllocator Allocator;
      
        struct BVHNBuilderV {
          NodeRef build(FastAllocator* allocator, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings);
          virtual NodeRef createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) = 0;
        };

        template<typename CreateLeafFunc>
        struct BVHNBuilderT : public BVHNBuilderV
        {
          BVHNBuilderT (CreateLeafFunc createLeafFunc)
            : createLeafFunc(createLeafFunc) {}

          NodeRef createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) {
            return createLeafFunc(prims,set,alloc);
          }

        private:
          CreateLeafFunc createLeafFunc;
        };

        template<typename CreateLeafFunc>
        static NodeRef build(FastAllocator* allocator, CreateLeafFunc createLeaf, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings) {
          return BVHNBuilderT<CreateLeafFunc>(createLeaf).build(allocator,progress,prims,pinfo,settings);
        }
      };

    template<int N>
      struct BVHNBuilderQuantizedVirtual
      {
        typedef BVHN<N> BVH;
        typedef typename BVH::NodeRef NodeRef;
        typedef FastAllocator::CachedAllocator Allocator;
      
        struct BVHNBuilderV {
          NodeRef build(FastAllocator* allocator, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings);
          virtual NodeRef createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) = 0;
        };

        template<typename CreateLeafFunc>
        struct BVHNBuilderT : public BVHNBuilderV
        {
          BVHNBuilderT (CreateLeafFunc createLeafFunc)
            : createLeafFunc(createLeafFunc) {}

          NodeRef createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) {
            return createLeafFunc(prims,set,alloc);
          }

        private:
          CreateLeafFunc createLeafFunc;
        };

        template<typename CreateLeafFunc>
        static NodeRef build(FastAllocator* allocator, CreateLeafFunc createLeaf, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings) {
          return BVHNBuilderT<CreateLeafFunc>(createLeaf).build(allocator,progress,prims,pinfo,settings);
        }
      };

    template<int N>
      struct BVHNBuilderMblurVirtual
      {
        typedef BVHN<N> BVH;
        typedef typename BVH::AABBNodeMB AABBNodeMB;
        typedef typename BVH::NodeRef NodeRef;
        typedef typename BVH::NodeRecordMB NodeRecordMB;
        typedef FastAllocator::CachedAllocator Allocator;
      
        struct BVHNBuilderV {
          NodeRecordMB build(FastAllocator* allocator, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings, const BBox1f& timeRange);
          virtual NodeRecordMB createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) = 0;
        };

        template<typename CreateLeafFunc>
        struct BVHNBuilderT : public BVHNBuilderV
        {
          BVHNBuilderT (CreateLeafFunc createLeafFunc)
            : createLeafFunc(createLeafFunc) {}

          NodeRecordMB createLeaf (const PrimRef* prims, const range<size_t>& set, const Allocator& alloc) {
            return createLeafFunc(prims,set,alloc);
          }

        private:
          CreateLeafFunc createLeafFunc;
        };

        template<typename CreateLeafFunc>
        static NodeRecordMB build(FastAllocator* allocator, CreateLeafFunc createLeaf, BuildProgressMonitor& progress, PrimRef* prims, const PrimInfo& pinfo, GeneralBVHBuilder::Settings settings, const BBox1f& timeRange) {
          return BVHNBuilderT<CreateLeafFunc>(createLeaf).build(allocator,progress,prims,pinfo,settings,timeRange);
        }
      };
  }
}
