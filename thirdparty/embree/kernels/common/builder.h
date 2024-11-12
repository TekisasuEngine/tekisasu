/**************************************************************************/
/*  builder.h                                                             */
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

#include "default.h"
#include "accel.h"

namespace embree
{  
#define MODE_HIGH_QUALITY (1<<8)

  /*! virtual interface for all hierarchy builders */
  class Builder : public RefCount {
  public:

    static const size_t DEFAULT_SINGLE_THREAD_THRESHOLD = 1024;

    /*! initiates the hierarchy builder */
    virtual void build() = 0;

    /*! notifies the builder about the deletion of some geometry */
    virtual void deleteGeometry(size_t geomID) {};

    /*! clears internal builder state */
    virtual void clear() = 0;
  };

  /*! virtual interface for progress monitor class */
  struct BuildProgressMonitor {
    virtual void operator() (size_t dn) const = 0;
  };

  /*! build the progress monitor interface from a closure */
  template<typename Closure>
    struct ProgressMonitorClosure : BuildProgressMonitor
  {
  public:
    ProgressMonitorClosure (const Closure& closure) : closure(closure) {}
    void operator() (size_t dn) const { closure(dn); }
  private:
    const Closure closure;
  };
  template<typename Closure> __forceinline const ProgressMonitorClosure<Closure> BuildProgressMonitorFromClosure(const Closure& closure) {
    return ProgressMonitorClosure<Closure>(closure);
  }

  struct LineSegments;
  struct TriangleMesh;
  struct QuadMesh;
  struct UserGeometry;

  class Scene;

  typedef void (*createLineSegmentsAccelTy)(Scene* scene, LineSegments* mesh, AccelData*& accel, Builder*& builder);
  typedef void (*createTriangleMeshAccelTy)(Scene* scene, unsigned int geomID, AccelData*& accel, Builder*& builder);
  typedef void (*createQuadMeshAccelTy)(Scene* scene, unsigned int geomID, AccelData*& accel, Builder*& builder);
  typedef void (*createUserGeometryAccelTy)(Scene* scene, unsigned int geomID, AccelData*& accel, Builder*& builder);

}
