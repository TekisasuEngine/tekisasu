/**************************************************************************/
/*  rtcore_buffer.h                                                       */
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

#include "rtcore_device.h"

RTC_NAMESPACE_BEGIN

/* Types of buffers */
enum RTCBufferType
{
  RTC_BUFFER_TYPE_INDEX            = 0,
  RTC_BUFFER_TYPE_VERTEX           = 1,
  RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE = 2,
  RTC_BUFFER_TYPE_NORMAL           = 3,
  RTC_BUFFER_TYPE_TANGENT          = 4,
  RTC_BUFFER_TYPE_NORMAL_DERIVATIVE = 5,

  RTC_BUFFER_TYPE_GRID                 = 8,

  RTC_BUFFER_TYPE_FACE                 = 16,
  RTC_BUFFER_TYPE_LEVEL                = 17,
  RTC_BUFFER_TYPE_EDGE_CREASE_INDEX    = 18,
  RTC_BUFFER_TYPE_EDGE_CREASE_WEIGHT   = 19,
  RTC_BUFFER_TYPE_VERTEX_CREASE_INDEX  = 20,
  RTC_BUFFER_TYPE_VERTEX_CREASE_WEIGHT = 21,
  RTC_BUFFER_TYPE_HOLE                 = 22,

  RTC_BUFFER_TYPE_TRANSFORM            = 23,

  RTC_BUFFER_TYPE_FLAGS = 32
};

/* Opaque buffer type */
typedef struct RTCBufferTy* RTCBuffer;

/* Creates a new buffer. */
RTC_API RTCBuffer rtcNewBuffer(RTCDevice device, size_t byteSize);

/* Creates a new shared buffer. */
RTC_API RTCBuffer rtcNewSharedBuffer(RTCDevice device, void* ptr, size_t byteSize);

/* Returns a pointer to the buffer data. */
RTC_API void* rtcGetBufferData(RTCBuffer buffer);

/* Retains the buffer (increments the reference count). */
RTC_API void rtcRetainBuffer(RTCBuffer buffer);

/* Releases the buffer (decrements the reference count). */
RTC_API void rtcReleaseBuffer(RTCBuffer buffer);

RTC_NAMESPACE_END
