/**************************************************************************/
/*  config.h                                                              */
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

#include "../include/embree4/rtcore_config.h"

// #cmakedefine EMBREE_RAY_MASK
// #cmakedefine EMBREE_STAT_COUNTERS
// #cmakedefine EMBREE_BACKFACE_CULLING
// #cmakedefine EMBREE_BACKFACE_CULLING_CURVES
// #cmakedefine EMBREE_BACKFACE_CULLING_SPHERES
#define EMBREE_FILTER_FUNCTION
// #cmakedefine EMBREE_IGNORE_INVALID_RAYS
#define EMBREE_GEOMETRY_TRIANGLE
// #cmakedefine EMBREE_GEOMETRY_QUAD
// #cmakedefine EMBREE_GEOMETRY_CURVE
// #cmakedefine EMBREE_GEOMETRY_SUBDIVISION
// #cmakedefine EMBREE_GEOMETRY_USER
// #cmakedefine EMBREE_GEOMETRY_INSTANCE
// EMBREE_GEOMETRY_INSTANCE_ARRAY is defined in rtcore_config.h
// #cmakedefine EMBREE_GEOMETRY_GRID
// #cmakedefine EMBREE_GEOMETRY_POINT
#define EMBREE_RAY_PACKETS
// #cmakedefine EMBREE_COMPACT_POLYS

#define EMBREE_CURVE_SELF_INTERSECTION_AVOIDANCE_FACTOR 2.0
#define EMBREE_DISC_POINT_SELF_INTERSECTION_AVOIDANCE

#if defined(EMBREE_GEOMETRY_TRIANGLE)
  #define IF_ENABLED_TRIS(x) x
#else
  #define IF_ENABLED_TRIS(x)
#endif

#if defined(EMBREE_GEOMETRY_QUAD)
  #define IF_ENABLED_QUADS(x) x
#else
  #define IF_ENABLED_QUADS(x)
#endif

#if defined(EMBREE_GEOMETRY_CURVE) || defined(EMBREE_GEOMETRY_POINT)
  #define IF_ENABLED_CURVES_OR_POINTS(x) x
#else
  #define IF_ENABLED_CURVES_OR_POINTS(x)
#endif

#if defined(EMBREE_GEOMETRY_CURVE)
  #define IF_ENABLED_CURVES(x) x
#else
  #define IF_ENABLED_CURVES(x)
#endif

#if defined(EMBREE_GEOMETRY_POINT)
  #define IF_ENABLED_POINTS(x) x
#else
  #define IF_ENABLED_POINTS(x)
#endif

#if defined(EMBREE_GEOMETRY_SUBDIVISION)
  #define IF_ENABLED_SUBDIV(x) x
#else
  #define IF_ENABLED_SUBDIV(x)
#endif

#if defined(EMBREE_GEOMETRY_USER)
  #define IF_ENABLED_USER(x) x
#else
  #define IF_ENABLED_USER(x)
#endif

#if defined(EMBREE_GEOMETRY_INSTANCE)
  #define IF_ENABLED_INSTANCE(x) x
#else
  #define IF_ENABLED_INSTANCE(x)
#endif

#if defined(EMBREE_GEOMETRY_INSTANCE_ARRAY)
  #define IF_ENABLED_INSTANCE_ARRAY(x) x
#else
  #define IF_ENABLED_INSTANCE_ARRAY(x)
#endif

#if defined(EMBREE_GEOMETRY_GRID)
  #define IF_ENABLED_GRIDS(x) x
#else
  #define IF_ENABLED_GRIDS(x)
#endif




