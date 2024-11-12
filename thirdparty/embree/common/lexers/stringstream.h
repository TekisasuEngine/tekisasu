/**************************************************************************/
/*  stringstream.h                                                        */
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

#include "stream.h"

namespace embree
{
  /*! simple tokenizer that produces a string stream */
  class StringStream : public Stream<std::string>
  {
  public:
    StringStream(const Ref<Stream<int> >& cin, const std::string& seps = "\n\t\r ",
                 const std::string& endl = "", bool multiLine = false);
  public:
    ParseLocation location() { return cin->loc(); }
    std::string next();
  private:
    __forceinline bool isSeparator(unsigned int c) const { return c<256 && isSepMap[c]; }
    __forceinline bool isValidChar(unsigned int c) const { return c<256 && isValidCharMap[c]; }
  private:
    Ref<Stream<int> > cin; /*! source character stream */
    bool isSepMap[256];    /*! map for fast classification of separators */
    bool isValidCharMap[256];  /*! map for valid characters */
    std::string endl;      /*! the token of the end of line */
    bool multiLine;        /*! whether to parse lines wrapped with \ */
  };
}
