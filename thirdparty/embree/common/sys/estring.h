/**************************************************************************/
/*  estring.h                                                             */
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

#include "platform.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"

namespace embree
{
  class IOStreamStateRestorer 
  {
  public:
    IOStreamStateRestorer(std::ostream& iostream)
      : iostream(iostream), flags(iostream.flags()), precision(iostream.precision()) {
    }

    ~IOStreamStateRestorer() {
      iostream.flags(flags);
      iostream.precision(precision);
    }
    
  private:
    std::ostream& iostream;
    std::ios::fmtflags flags;
    std::streamsize precision;
  };

  struct IndentOStream : public std::streambuf
  {
    explicit IndentOStream(std::ostream &ostream, int indent = 2)
      : streambuf(ostream.rdbuf())
      , start_of_line(true)
      , ident_str(indent, ' ')
      , stream(&ostream)
    {
      // set streambuf of ostream to this and save original streambuf
      stream->rdbuf(this);
    }

    virtual ~IndentOStream()
    {
      if (stream != NULL) {
        // restore old streambuf
        stream->rdbuf(streambuf);
      }
    }

  protected:
    virtual int overflow(int ch) {
      if (start_of_line && ch != '\n') {
        streambuf->sputn(ident_str.data(), ident_str.size());
      }
      start_of_line = ch == '\n';
      return streambuf->sputc(ch);
    }

  private:
    std::streambuf *streambuf;
    bool start_of_line;
    std::string ident_str;
    std::ostream *stream;
  };

  std::string toLowerCase(const std::string& s);
  std::string toUpperCase(const std::string& s);

  Vec2f string_to_Vec2f ( std::string str );
  Vec3f string_to_Vec3f ( std::string str );
  Vec4f string_to_Vec4f ( std::string str );
}
