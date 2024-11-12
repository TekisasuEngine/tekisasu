/**************************************************************************/
/*  estring.cpp                                                           */
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

#include "estring.h"

#include <algorithm>
#include <ctype.h>

namespace embree
{
  char to_lower(char c) { return char(tolower(int(c))); }
  char to_upper(char c) { return char(toupper(int(c))); }
  std::string toLowerCase(const std::string& s) { std::string dst(s); std::transform(dst.begin(), dst.end(), dst.begin(), to_lower); return dst; }
  std::string toUpperCase(const std::string& s) { std::string dst(s); std::transform(dst.begin(), dst.end(), dst.begin(), to_upper); return dst; }

  Vec2f string_to_Vec2f ( std::string str )
  {
    size_t next = 0;
    const float x = std::stof(str,&next); str = str.substr(next+1);
    const float y = std::stof(str,&next);
    return Vec2f(x,y);
  }
  
  Vec3f string_to_Vec3f ( std::string str )
  {
    size_t next = 0;
    const float x = std::stof(str,&next); str = str.substr(next+1);
    const float y = std::stof(str,&next); str = str.substr(next+1);
    const float z = std::stof(str,&next); 
    return Vec3f(x,y,z);
  }
  
  Vec4f string_to_Vec4f ( std::string str )
  {
    size_t next = 0;
    const float x = std::stof(str,&next); str = str.substr(next+1);
    const float y = std::stof(str,&next); str = str.substr(next+1);
    const float z = std::stof(str,&next); str = str.substr(next+1);
    const float w = std::stof(str,&next);
    return Vec4f(x,y,z,w);
  }
}
