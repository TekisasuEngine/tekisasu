/**************************************************************************/
/*  acceln.h                                                              */
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

#include "accel.h"

namespace embree
{
  /*! merges N acceleration structures together, by processing them in order */
  class AccelN : public Accel
  {
  public:
    AccelN ();
    ~AccelN();

  public:
    void accels_add(Accel* accel);
    void accels_init();

  public:
    static bool pointQuery (Accel::Intersectors* This, PointQuery* query, PointQueryContext* context);

  public:
    static void intersect (Accel::Intersectors* This, RTCRayHit& ray, RayQueryContext* context);
    static void intersect4 (const void* valid, Accel::Intersectors* This, RTCRayHit4& ray, RayQueryContext* context);
    static void intersect8 (const void* valid, Accel::Intersectors* This, RTCRayHit8& ray, RayQueryContext* context);
    static void intersect16 (const void* valid, Accel::Intersectors* This, RTCRayHit16& ray, RayQueryContext* context);

  public:
    static void occluded (Accel::Intersectors* This, RTCRay& ray, RayQueryContext* context);
    static void occluded4 (const void* valid, Accel::Intersectors* This, RTCRay4& ray, RayQueryContext* context);
    static void occluded8 (const void* valid, Accel::Intersectors* This, RTCRay8& ray, RayQueryContext* context);
    static void occluded16 (const void* valid, Accel::Intersectors* This, RTCRay16& ray, RayQueryContext* context);

  public:
    void accels_print(size_t ident);
    void accels_immutable();
    void accels_build ();
    void accels_select(bool filter);
    void accels_deleteGeometry(size_t geomID);
    void accels_clear ();

  public:
    std::vector<Accel*> accels;
  };
}
