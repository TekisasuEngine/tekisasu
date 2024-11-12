/**************************************************************************/
/*  rtcore.h                                                              */
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

#include "../../include/embree4/rtcore.h"
RTC_NAMESPACE_USE

namespace embree
{  
  /*! decoding of intersection flags */
  __forceinline bool isCoherent  (RTCRayQueryFlags flags) { return (flags & RTC_RAY_QUERY_FLAG_COHERENT) == RTC_RAY_QUERY_FLAG_COHERENT; }
  __forceinline bool isIncoherent(RTCRayQueryFlags flags) { return (flags & RTC_RAY_QUERY_FLAG_COHERENT) == RTC_RAY_QUERY_FLAG_INCOHERENT; }

/*! Macros used in the rtcore API implementation */
// -- GODOT start --
#define RTC_CATCH_BEGIN
#define RTC_CATCH_END(device)
#define RTC_CATCH_END2(scene)
#define RTC_CATCH_END2_FALSE(scene) return false;
#if 0
// -- GODOT end --
#define RTC_CATCH_BEGIN try {
  
#define RTC_CATCH_END(device)                                                \
  } catch (std::bad_alloc&) {                                                   \
    Device::process_error(device,RTC_ERROR_OUT_OF_MEMORY,"out of memory");      \
  } catch (rtcore_error& e) {                                                   \
    Device::process_error(device,e.error,e.what());                             \
  } catch (std::exception& e) {                                                 \
    Device::process_error(device,RTC_ERROR_UNKNOWN,e.what());                   \
  } catch (...) {                                                               \
    Device::process_error(device,RTC_ERROR_UNKNOWN,"unknown exception caught"); \
  }
  
#define RTC_CATCH_END2(scene)                                                \
  } catch (std::bad_alloc&) {                                                   \
    Device* device = scene ? scene->device : nullptr;		\
    Device::process_error(device,RTC_ERROR_OUT_OF_MEMORY,"out of memory");      \
  } catch (rtcore_error& e) {                                                   \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,e.error,e.what());                             \
  } catch (std::exception& e) {                                                 \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,RTC_ERROR_UNKNOWN,e.what());                   \
  } catch (...) {                                                               \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,RTC_ERROR_UNKNOWN,"unknown exception caught"); \
  }

#define RTC_CATCH_END2_FALSE(scene)                                             \
  } catch (std::bad_alloc&) {                                                   \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,RTC_ERROR_OUT_OF_MEMORY,"out of memory");      \
    return false;                                                               \
  } catch (rtcore_error& e) {                                                   \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,e.error,e.what());                             \
    return false;                                                               \
  } catch (std::exception& e) {                                                 \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,RTC_ERROR_UNKNOWN,e.what());                   \
    return false;                                                               \
  } catch (...) {                                                               \
    Device* device = scene ? scene->device : nullptr;                           \
    Device::process_error(device,RTC_ERROR_UNKNOWN,"unknown exception caught"); \
    return false;                                                               \
  }

#endif
  
#define RTC_VERIFY_HANDLE(handle)                               \
  if (handle == nullptr) {                                         \
    throw_RTCError(RTC_ERROR_INVALID_ARGUMENT,"invalid argument"); \
  }

#define RTC_VERIFY_GEOMID(id)                                   \
  if (id == RTC_INVALID_GEOMETRY_ID) {                             \
    throw_RTCError(RTC_ERROR_INVALID_ARGUMENT,"invalid argument"); \
  }

#define RTC_VERIFY_UPPER(id,upper)                              \
  if (id > upper) {                                                \
    throw_RTCError(RTC_ERROR_INVALID_ARGUMENT,"invalid argument"); \
  }

#define RTC_VERIFY_RANGE(id,lower,upper)	\
  if (id < lower || id > upper)						  \
    throw_RTCError(RTC_ERROR_INVALID_OPERATION,"argument out of bounds");
  
#if 0 // enable to debug print all API calls
#define RTC_TRACE(x) std::cout << #x << std::endl;
#else
#define RTC_TRACE(x) 
#endif

// -- GODOT start --
#if 0
  /*! used to throw embree API errors */
  struct rtcore_error : public std::exception
  {
    __forceinline rtcore_error(RTCError error, const std::string& str)
      : error(error), str(str) {}
    
    ~rtcore_error() throw() {}
    
    const char* what () const throw () {
      return str.c_str();
    }
    
    RTCError error;
    std::string str;
  };
#endif

#if defined(DEBUG) // only report file and line in debug mode
  #define throw_RTCError(error,str) \
    printf("%s (%d): %s", __FILE__, __LINE__, std::string(str).c_str()), abort();
    // throw rtcore_error(error,std::string(__FILE__) + " (" + toString(__LINE__) + "): " + std::string(str));
#else
  #define throw_RTCError(error,str) \
    abort();
    // throw rtcore_error(error,str);
#endif
// -- GODOT end --

#define RTC_BUILD_ARGUMENTS_HAS(settings,member) \
  (settings.byteSize > (offsetof(RTCBuildArguments,member)+sizeof(settings.member)))

  
  inline void storeTransform(const AffineSpace3fa& space, RTCFormat format, float* xfm)
  {
    switch (format)
    {
    case RTC_FORMAT_FLOAT3X4_ROW_MAJOR:
      xfm[ 0] = space.l.vx.x;  xfm[ 1] = space.l.vy.x;  xfm[ 2] = space.l.vz.x;  xfm[ 3] = space.p.x;
      xfm[ 4] = space.l.vx.y;  xfm[ 5] = space.l.vy.y;  xfm[ 6] = space.l.vz.y;  xfm[ 7] = space.p.y;
      xfm[ 8] = space.l.vx.z;  xfm[ 9] = space.l.vy.z;  xfm[10] = space.l.vz.z;  xfm[11] = space.p.z;
      break;

    case RTC_FORMAT_FLOAT3X4_COLUMN_MAJOR:
      xfm[ 0] = space.l.vx.x;  xfm[ 1] = space.l.vx.y;  xfm[ 2] = space.l.vx.z;
      xfm[ 3] = space.l.vy.x;  xfm[ 4] = space.l.vy.y;  xfm[ 5] = space.l.vy.z;
      xfm[ 6] = space.l.vz.x;  xfm[ 7] = space.l.vz.y;  xfm[ 8] = space.l.vz.z;
      xfm[ 9] = space.p.x;     xfm[10] = space.p.y;     xfm[11] = space.p.z;
      break;

    case RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR:
      xfm[ 0] = space.l.vx.x;  xfm[ 1] = space.l.vx.y;  xfm[ 2] = space.l.vx.z;  xfm[ 3] = 0.f;
      xfm[ 4] = space.l.vy.x;  xfm[ 5] = space.l.vy.y;  xfm[ 6] = space.l.vy.z;  xfm[ 7] = 0.f;
      xfm[ 8] = space.l.vz.x;  xfm[ 9] = space.l.vz.y;  xfm[10] = space.l.vz.z;  xfm[11] = 0.f;
      xfm[12] = space.p.x;     xfm[13] = space.p.y;     xfm[14] = space.p.z;     xfm[15] = 1.f;
      break;

    default:
#if !defined(__SYCL_DEVICE_ONLY__)
      throw_RTCError(RTC_ERROR_INVALID_OPERATION, "invalid matrix format");
#endif
      break;
    }
  }
}
