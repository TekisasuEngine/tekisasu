/**************************************************************************/
/*  parallel_map.h                                                        */
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
  /*! implementation of a key/value map with parallel construction */
  template<typename Key, typename Val>
  class parallel_map
  {
    /* key/value pair to build the map */
    struct KeyValue
    {
      __forceinline KeyValue () {}

      __forceinline KeyValue (const Key key, const Val val)
	: key(key), val(val) {}

      __forceinline operator Key() const {
	return key;
      }

    public:
      Key key;
      Val val;
    };

  public:
    
    /*! parallel map constructors */
    parallel_map () {}

    /*! construction from pair of vectors */
    template<typename KeyVector, typename ValVector>
      parallel_map (const KeyVector& keys, const ValVector& values) { init(keys,values); }

    /*! initialized the parallel map from a vector with keys and values */
    template<typename KeyVector, typename ValVector>
      void init(const KeyVector& keys, const ValVector& values) 
    {
      /* reserve sufficient space for all data */
      assert(keys.size() == values.size());
      vec.resize(keys.size());
      
      /* generate key/value pairs */
      parallel_for( size_t(0), keys.size(), size_t(4*4096), [&](const range<size_t>& r) {
	for (size_t i=r.begin(); i<r.end(); i++)
	  vec[i] = KeyValue((Key)keys[i],values[i]);
      });

      /* perform parallel radix sort of the key/value pairs */
      std::vector<KeyValue> temp(keys.size());
      radix_sort<KeyValue,Key>(vec.data(),temp.data(),keys.size());
    }

    /*! Returns a pointer to the value associated with the specified key. The pointer will be nullptr of the key is not contained in the map. */
    __forceinline const Val* lookup(const Key& key) const 
    {
      typename std::vector<KeyValue>::const_iterator i = std::lower_bound(vec.begin(), vec.end(), key);
      if (i == vec.end()) return nullptr;
      if (i->key != key) return nullptr;
      return &i->val;
    }

    /*! If the key is in the map, the function returns the value associated with the key, otherwise it returns the default value. */
    __forceinline Val lookup(const Key& key, const Val& def) const 
    {
      typename std::vector<KeyValue>::const_iterator i = std::lower_bound(vec.begin(), vec.end(), key);
      if (i == vec.end()) return def;
      if (i->key != key) return def;
      return i->val;
    }

    /*! clears all state */
    void clear() {
      vec.clear();
    }

  private:
    std::vector<KeyValue> vec;    //!< vector containing sorted elements
  };
}
