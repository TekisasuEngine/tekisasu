/**************************************************************************/
/*  bvh_intersector_hybrid.h                                              */
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

#include "bvh.h"
#include "../common/ray.h"
#include "../common/stack_item.h"
#include "node_intersector_frustum.h"

namespace embree
{
  namespace isa 
  {
    template<int K, bool robust>
    struct TravRayK;

    /*! BVH hybrid packet intersector. Switches between packet and single ray traversal (optional). */
    template<int N, int K, int types, bool robust, typename PrimitiveIntersectorK, bool single = true>
    class BVHNIntersectorKHybrid
    {
      /* shortcuts for frequently used types */
      typedef typename PrimitiveIntersectorK::Precalculations Precalculations;
      typedef typename PrimitiveIntersectorK::Primitive Primitive;
      typedef BVHN<N> BVH;
      typedef typename BVH::NodeRef NodeRef;
      typedef typename BVH::BaseNode BaseNode;
      typedef typename BVH::AABBNode AABBNode;
      
      static const size_t stackSizeSingle = 1+(N-1)*BVH::maxDepth+3; // +3 due to 16-wide store
      static const size_t stackSizeChunk = 1+(N-1)*BVH::maxDepth;

      static const size_t switchThresholdIncoherent = \
      (K==4)  ? 3 :
      (K==8)  ? ((N==4) ? 5 : 7) :
      (K==16) ? 14 : // 14 seems to work best for KNL due to better ordered chunk traversal
      0;

    private:
      static void intersect1(Accel::Intersectors* This, const BVH* bvh, NodeRef root, size_t k, Precalculations& pre,
                             RayHitK<K>& ray, const TravRayK<K, robust>& tray, RayQueryContext* context);
      static bool occluded1(Accel::Intersectors* This, const BVH* bvh, NodeRef root, size_t k, Precalculations& pre,
                            RayK<K>& ray, const TravRayK<K, robust>& tray, RayQueryContext* context);

    public:
      static void intersect(vint<K>* valid, Accel::Intersectors* This, RayHitK<K>& ray, RayQueryContext* context);
      static void occluded (vint<K>* valid, Accel::Intersectors* This, RayK<K>& ray, RayQueryContext* context);

      static void intersectCoherent(vint<K>* valid, Accel::Intersectors* This, RayHitK<K>& ray, RayQueryContext* context);
      static void occludedCoherent (vint<K>* valid, Accel::Intersectors* This, RayK<K>& ray, RayQueryContext* context);

    };

    /*! BVH packet intersector. */
    template<int N, int K, int types, bool robust, typename PrimitiveIntersectorK>
    class BVHNIntersectorKChunk : public BVHNIntersectorKHybrid<N, K, types, robust, PrimitiveIntersectorK, false> {};
  }
}
