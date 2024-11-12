/**************************************************************************/
/*  filter_sycl.h                                                         */
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

#include "../common/geometry.h"
#include "../common/ray.h"
#include "../common/hit.h"
#include "../common/context.h"

namespace embree
{
  __forceinline bool runIntersectionFilter1Helper(RTCFilterFunctionNArguments* args, int& mask, const Geometry* const geometry, RayQueryContext* context)
  {
    typedef void (*RTCFilterFunctionSYCL)(const void* args);
    const RTCFeatureFlags feature_mask MAYBE_UNUSED = context->args->feature_mask;
    
#if EMBREE_SYCL_GEOMETRY_CALLBACK
    if (feature_mask & RTC_FEATURE_FLAG_FILTER_FUNCTION_IN_GEOMETRY)
    {
      RTCFilterFunctionSYCL gfilter = (RTCFilterFunctionSYCL) geometry->intersectionFilterN;
      if (gfilter)
      {
        gfilter(args);
        
        if (mask == 0)
          return false;
      }
    }
#endif

    if (feature_mask & RTC_FEATURE_FLAG_FILTER_FUNCTION_IN_ARGUMENTS)
    {
      RTCFilterFunctionSYCL cfilter = (RTCFilterFunctionSYCL) context->args->filter;
      if (cfilter)
      {
        if (context->enforceArgumentFilterFunction() || geometry->hasArgumentFilterFunctions())
          cfilter(args);
        
        if (mask == 0)
          return false;
      }
    }
    
    return true;
  }

  __forceinline bool runOcclusionFilter1Helper(RTCFilterFunctionNArguments* args, int& mask, const Geometry* const geometry, RayQueryContext* context)
  {
    typedef void (*RTCFilterFunctionSYCL)(const void* args);
    const RTCFeatureFlags feature_mask MAYBE_UNUSED = context->args->feature_mask;
    
#if EMBREE_SYCL_GEOMETRY_CALLBACK
    if (feature_mask & RTC_FEATURE_FLAG_FILTER_FUNCTION_IN_GEOMETRY)
    {
      RTCFilterFunctionSYCL gfilter = (RTCFilterFunctionSYCL) geometry->occlusionFilterN;
      if (gfilter)
      {
        gfilter(args);
        
        if (mask == 0)
          return false;
      }
    }
#endif

    if (feature_mask & RTC_FEATURE_FLAG_FILTER_FUNCTION_IN_ARGUMENTS)
    {
      RTCFilterFunctionSYCL cfilter = (RTCFilterFunctionSYCL) context->args->filter;
      if (cfilter)
      {
        if (context->enforceArgumentFilterFunction() || geometry->hasArgumentFilterFunctions())
          cfilter(args);
        
        if (mask == 0)
          return false;
      }
    }

    return true;
  }
  
  __forceinline bool runIntersectionFilter1SYCL(Geometry* geometry, RayHit& ray, sycl::private_ptr<RayQueryContext> context, Hit& hit)
  {
    RTCFilterFunctionNArguments args;
    int mask = -1;
    args.valid = &mask;
    args.geometryUserPtr = geometry->userPtr;
    args.context = context->user;
    args.ray = (RTCRayN*) &ray;
    args.hit = (RTCHitN*) &hit;
    args.N = 1;
    return runIntersectionFilter1Helper(&args,mask,geometry,context);
  }


  __forceinline bool runIntersectionFilter1SYCL(Geometry* geometry, Ray& ray, sycl::private_ptr<RayQueryContext> context, Hit& hit)
  {
    RTCFilterFunctionNArguments args;
    int mask = -1;
    args.valid = &mask;
    args.geometryUserPtr = geometry->userPtr;
    args.context = context->user;
    args.ray = (RTCRayN*) &ray;
    args.hit = (RTCHitN*) &hit;
    args.N = 1;
    return runOcclusionFilter1Helper(&args,mask,geometry,context);
  }
}
