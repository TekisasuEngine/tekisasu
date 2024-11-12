/**************************************************************************/
/*  bvh_intersector1_bvh4.cpp                                             */
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

#include "bvh_intersector1.cpp"

namespace embree
{
  namespace isa
  {
    int getISA() {
      return VerifyMultiTargetLinking::getISA();
    }

    ////////////////////////////////////////////////////////////////////////////////
    /// BVH4Intersector1 Definitions
    ////////////////////////////////////////////////////////////////////////////////

    IF_ENABLED_CURVES_OR_POINTS(DEFINE_INTERSECTOR1(BVH4OBBVirtualCurveIntersector1,BVHNIntersector1<4 COMMA BVH_AN1_UN1 COMMA false COMMA VirtualCurveIntersector1 >));
    IF_ENABLED_CURVES_OR_POINTS(DEFINE_INTERSECTOR1(BVH4OBBVirtualCurveIntersector1MB,BVHNIntersector1<4 COMMA BVH_AN2_AN4D_UN2 COMMA false COMMA VirtualCurveIntersector1 >));

    IF_ENABLED_CURVES_OR_POINTS(DEFINE_INTERSECTOR1(BVH4OBBVirtualCurveIntersectorRobust1,BVHNIntersector1<4 COMMA BVH_AN1_UN1 COMMA true COMMA VirtualCurveIntersector1 >));
    IF_ENABLED_CURVES_OR_POINTS(DEFINE_INTERSECTOR1(BVH4OBBVirtualCurveIntersectorRobust1MB,BVHNIntersector1<4 COMMA BVH_AN2_AN4D_UN2 COMMA true COMMA VirtualCurveIntersector1 >));

    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4Intersector1Moeller,  BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<TriangleMIntersector1Moeller  <4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4iIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<TriangleMiIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4vIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true  COMMA ArrayIntersector1<TriangleMvIntersector1Pluecker<4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4iIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true  COMMA ArrayIntersector1<TriangleMiIntersector1Pluecker<4 COMMA true> > >));

    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4vMBIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<TriangleMvMBIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4iMBIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<TriangleMiMBIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4vMBIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA true  COMMA ArrayIntersector1<TriangleMvMBIntersector1Pluecker<4 COMMA true> > >));
    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(BVH4Triangle4iMBIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA true  COMMA ArrayIntersector1<TriangleMiMBIntersector1Pluecker<4 COMMA true> > >));

    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4vIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<QuadMvIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4iIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<QuadMiIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4vIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true  COMMA ArrayIntersector1<QuadMvIntersector1Pluecker<4 COMMA true> > >));
    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4iIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true  COMMA ArrayIntersector1<QuadMiIntersector1Pluecker<4 COMMA true> > >));

    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4iMBIntersector1Moeller, BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<QuadMiMBIntersector1Moeller <4 COMMA true> > >));
    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(BVH4Quad4iMBIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA true  COMMA ArrayIntersector1<QuadMiMBIntersector1Pluecker<4 COMMA true> > >));

    IF_ENABLED_SUBDIV(DEFINE_INTERSECTOR1(BVH4SubdivPatch1Intersector1,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true COMMA SubdivPatch1Intersector1>));
    IF_ENABLED_SUBDIV(DEFINE_INTERSECTOR1(BVH4SubdivPatch1MBIntersector1,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA true COMMA SubdivPatch1MBIntersector1>));
    
    IF_ENABLED_USER(DEFINE_INTERSECTOR1(BVH4VirtualIntersector1,BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<ObjectIntersector1<false>> >));
    IF_ENABLED_USER(DEFINE_INTERSECTOR1(BVH4VirtualMBIntersector1,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<ObjectIntersector1<true>> >));

    IF_ENABLED_INSTANCE(DEFINE_INTERSECTOR1(BVH4InstanceIntersector1,BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<InstanceIntersector1> >));
    IF_ENABLED_INSTANCE(DEFINE_INTERSECTOR1(BVH4InstanceMBIntersector1,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<InstanceIntersector1MB> >));

    IF_ENABLED_INSTANCE_ARRAY(DEFINE_INTERSECTOR1(BVH4InstanceArrayIntersector1,BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA ArrayIntersector1<InstanceArrayIntersector1> >));
    IF_ENABLED_INSTANCE_ARRAY(DEFINE_INTERSECTOR1(BVH4InstanceArrayMBIntersector1,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA ArrayIntersector1<InstanceArrayIntersector1MB> >));

    IF_ENABLED_TRIS(DEFINE_INTERSECTOR1(QBVH4Triangle4iIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_QN1 COMMA false COMMA ArrayIntersector1<TriangleMiIntersector1Pluecker<4 COMMA true> > >));
    IF_ENABLED_QUADS(DEFINE_INTERSECTOR1(QBVH4Quad4iIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_QN1 COMMA false COMMA ArrayIntersector1<QuadMiIntersector1Pluecker<4 COMMA true> > >));

    IF_ENABLED_GRIDS(DEFINE_INTERSECTOR1(BVH4GridIntersector1Moeller,BVHNIntersector1<4 COMMA BVH_AN1 COMMA false COMMA SubGridIntersector1Moeller<4 COMMA true> >));
    IF_ENABLED_GRIDS(DEFINE_INTERSECTOR1(BVH4GridMBIntersector1Moeller,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA true COMMA SubGridMBIntersector1Pluecker<4 COMMA true> >));

    IF_ENABLED_GRIDS(DEFINE_INTERSECTOR1(BVH4GridIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN1 COMMA true COMMA SubGridIntersector1Pluecker<4 COMMA true> >));
    //IF_ENABLED_GRIDS(DEFINE_INTERSECTOR1(BVH4GridMBIntersector1Pluecker,BVHNIntersector1<4 COMMA BVH_AN2_AN4D COMMA false COMMA SubGridMBIntersector1Pluecker<4 COMMA true> >));

  }
}
