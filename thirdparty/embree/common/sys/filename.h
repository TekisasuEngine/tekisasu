/**************************************************************************/
/*  filename.h                                                            */
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

namespace embree
{
  /*! Convenience class for handling file names and paths. */
  class FileName
  {
  public:

    /*! create an empty filename */
    FileName ();

    /*! create a valid filename from a string */
    FileName (const char* filename);

    /*! create a valid filename from a string */
    FileName (const std::string& filename);
    
    /*! returns path to home folder */
    static FileName homeFolder();

    /*! returns path to executable */
    static FileName executableFolder();

    /*! auto convert into a string */
    operator std::string() const { return filename; }

    /*! returns a string of the filename */
    const std::string str() const { return filename; }

    /*! returns a c-string of the filename */
    const char* c_str() const { return filename.c_str(); }

    /*! returns the path of a filename */
    FileName path() const;

    /*! returns the file of a filename  */
    std::string base() const;

    /*! returns the base of a filename without extension */
    std::string name() const;

    /*! returns the file extension */
    std::string ext() const;

    /*! drops the file extension */
    FileName dropExt() const;

    /*! replaces the file extension */
    FileName setExt(const std::string& ext = "") const;

    /*! adds file extension */
    FileName addExt(const std::string& ext = "") const;

    /*! concatenates two filenames to this/other */
    FileName operator +( const FileName& other ) const;

    /*! concatenates two filenames to this/other */
    FileName operator +( const std::string& other ) const;

    /*! removes the base from a filename (if possible) */
    FileName operator -( const FileName& base ) const;

    /*! == operator */
    friend bool operator==(const FileName& a, const FileName& b);

    /*! != operator */
    friend bool operator!=(const FileName& a, const FileName& b);

    /*! output operator */
    friend std::ostream& operator<<(std::ostream& cout, const FileName& filename);
   
  private:
    std::string filename;
  };
}
