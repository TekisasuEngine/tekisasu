/**************************************************************************/
/*  parallel_set.h                                                        */
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

#include "parallel_sort.h"

namespace embree
{
  /* implementation of a set of values with parallel construction */
  template<typename T>
  class parallel_set
  {
  public:

    /*! default constructor for the parallel set */
    parallel_set () {}

    /*! construction from vector */
    template<typename Vector>
      parallel_set (const Vector& in) { init(in); }

    /*! initialized the parallel set from a vector */
    template<typename Vector>
      void init(const Vector& in) 
    {
      /* copy data to internal vector */
      vec.resize(in.size());
      parallel_for( size_t(0), in.size(), size_t(4*4096), [&](const range<size_t>& r) {
	for (size_t i=r.begin(); i<r.end(); i++) 
	  vec[i] = in[i];
      });

      /* sort the data */
      std::vector<T> temp(in.size());
      radix_sort<T>(vec.data(),temp.data(),vec.size());
    }

    /*! tests if some element is in the set */
    __forceinline bool lookup(const T& elt) const {
      return std::binary_search(vec.begin(), vec.end(), elt);
    }

    /*! clears all state */
    void clear() {
      vec.clear();
    }

  private:
    std::vector<T> vec;   //!< vector containing sorted elements
  };
}
