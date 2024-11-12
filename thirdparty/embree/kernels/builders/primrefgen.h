/**************************************************************************/
/*  primrefgen.h                                                          */
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

#include "../common/scene.h"
#include "priminfo.h"
#include "priminfo_mb.h"
#include "bvh_builder_morton.h"

namespace embree
{ 
  namespace isa
  {
    PrimInfo createPrimRefArray(Geometry* geometry, unsigned int geomID, size_t numPrimitives, mvector<PrimRef>& prims, BuildProgressMonitor& progressMonitor);
   
    PrimInfo createPrimRefArray(Scene* scene, Geometry::GTypeMask types, bool mblur, size_t numPrimitives, mvector<PrimRef>& prims, BuildProgressMonitor& progressMonitor);

    PrimInfo createPrimRefArray(Scene* scene, Geometry::GTypeMask types, bool mblur, size_t numPrimitives, mvector<PrimRef>& prims, mvector<SubGridBuildData>& sgrids, BuildProgressMonitor& progressMonitor);
   
    PrimInfo createPrimRefArrayMBlur(Scene* scene, Geometry::GTypeMask types, size_t numPrimitives, mvector<PrimRef>& prims, BuildProgressMonitor& progressMonitor, size_t itime = 0);

    PrimInfoMB createPrimRefArrayMSMBlur(Scene* scene, Geometry::GTypeMask types, size_t numPrimitives, mvector<PrimRefMB>& prims, BuildProgressMonitor& progressMonitor, BBox1f t0t1 = BBox1f(0.0f,1.0f));

    PrimInfoMB createPrimRefArrayMSMBlur(Scene* scene, Geometry::GTypeMask types, size_t numPrimitives, mvector<PrimRefMB>& prims, mvector<SubGridBuildData>& sgrids, BuildProgressMonitor& progressMonitor, BBox1f t0t1 = BBox1f(0.0f,1.0f));

    template<typename Mesh>
      size_t createMortonCodeArray(Mesh* mesh, mvector<BVHBuilderMorton::BuildPrim>& morton, BuildProgressMonitor& progressMonitor);

    /* special variants for grids */
    PrimInfo createPrimRefArrayGrids(Scene* scene, mvector<PrimRef>& prims, mvector<SubGridBuildData>& sgrids); // FIXME: remove

    PrimInfo createPrimRefArrayGrids(GridMesh* mesh, mvector<PrimRef>& prims, mvector<SubGridBuildData>& sgrids);

    PrimInfoMB createPrimRefArrayMSMBlurGrid(Scene* scene, mvector<PrimRefMB>& prims, mvector<SubGridBuildData>& sgrids, BuildProgressMonitor& progressMonitor, BBox1f t0t1 = BBox1f(0.0f,1.0f));
  }
}
