/**************************************************************************/
/*  bvh_refit.h                                                           */
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

#pragma once

#include "../bvh/bvh.h"

namespace embree
{
  namespace isa
  {
    template<int N>
    class BVHNRefitter
    {
    public:

      /*! Type shortcuts */
      typedef BVHN<N> BVH;
      typedef typename BVH::AABBNode AABBNode;
      typedef typename BVH::NodeRef NodeRef;

      struct LeafBoundsInterface {
        virtual const BBox3fa leafBounds(NodeRef& ref) const = 0;
      };

    public:
    
      /*! Constructor. */
      BVHNRefitter (BVH* bvh, const LeafBoundsInterface& leafBounds);

      /*! refits the BVH */
      void refit();

    private:
      /* single-threaded subtree extraction based on BVH depth */
      void gather_subtree_refs(NodeRef& ref, 
                               size_t &subtrees,
                               const size_t depth = 0);

      /* single-threaded top-level refit */
      BBox3fa refit_toplevel(NodeRef& ref,
                             size_t &subtrees,
							 const BBox3fa *const subTreeBounds,
                             const size_t depth = 0);

      /* single-threaded subtree refit */
      BBox3fa recurse_bottom(NodeRef& ref);
      
    public:
      BVH* bvh;                              //!< BVH to refit
      const LeafBoundsInterface& leafBounds; //!< calculates bounds of leaves

      static const size_t MAX_SUB_TREE_EXTRACTION_DEPTH = (N==4) ? 4   : (N==8) ? 3    : 3;
      static const size_t MAX_NUM_SUB_TREES             = (N==4) ? 256 : (N==8) ? 512 : N*N*N; // N ^ MAX_SUB_TREE_EXTRACTION_DEPTH
      size_t numSubTrees;
      NodeRef subTrees[MAX_NUM_SUB_TREES];
    };

    template<int N, typename Mesh, typename Primitive>
    class BVHNRefitT : public Builder, public BVHNRefitter<N>::LeafBoundsInterface
    {
    public:
      
      /*! Type shortcuts */
      typedef BVHN<N> BVH;
      typedef typename BVH::AABBNode AABBNode;
      typedef typename BVH::NodeRef NodeRef;
      
    public:
      BVHNRefitT (BVH* bvh, Builder* builder, Mesh* mesh, size_t mode);

      virtual void build();
      
      virtual void clear();

      virtual const BBox3fa leafBounds (NodeRef& ref) const
      {
        size_t num; char* prim = ref.leaf(num);
        if (unlikely(ref == BVH::emptyNode)) return empty;

        BBox3fa bounds = empty;
        for (size_t i=0; i<num; i++)
            bounds.extend(((Primitive*)prim)[i].update(mesh));
        return bounds;
      }
      
    private:
      BVH* bvh;
      std::unique_ptr<Builder> builder;
      std::unique_ptr<BVHNRefitter<N>> refitter;
      Mesh* mesh;
      unsigned int topologyVersion;
    };
  }
}
