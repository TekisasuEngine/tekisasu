/**************************************************************************/
/*  shared_dictionary_internal.h                                          */
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

/* Copyright 2017 Google Inc. All Rights Reserved.

   Distributed under MIT license.
   See file LICENSE for detail or copy at https://opensource.org/licenses/MIT
*/

/* (Transparent) Shared Dictionary definition. */

#ifndef BROTLI_COMMON_SHARED_DICTIONARY_INTERNAL_H_
#define BROTLI_COMMON_SHARED_DICTIONARY_INTERNAL_H_

#include <brotli/shared_dictionary.h>
#include <brotli/types.h>

#include "dictionary.h"
#include "transform.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

struct BrotliSharedDictionaryStruct {
  /* LZ77 prefixes (compound dictionary). */
  uint32_t num_prefix;  /* max SHARED_BROTLI_MAX_COMPOUND_DICTS */
  size_t prefix_size[SHARED_BROTLI_MAX_COMPOUND_DICTS];
  const uint8_t* prefix[SHARED_BROTLI_MAX_COMPOUND_DICTS];

  /* If set, the context map is used to select word and transform list from 64
     contexts, if not set, the context map is not used and only words[0] and
     transforms[0] are to be used. */
  BROTLI_BOOL context_based;

  uint8_t context_map[SHARED_BROTLI_NUM_DICTIONARY_CONTEXTS];

  /* Amount of word_list+transform_list combinations. */
  uint8_t num_dictionaries;

  /* Must use num_dictionaries values. */
  const BrotliDictionary* words[SHARED_BROTLI_NUM_DICTIONARY_CONTEXTS];

  /* Must use num_dictionaries values. */
  const BrotliTransforms* transforms[SHARED_BROTLI_NUM_DICTIONARY_CONTEXTS];

  /* Amount of custom word lists. May be 0 if only Brotli's built-in is used */
  uint8_t num_word_lists;

  /* Contents of the custom words lists. Must be NULL if num_word_lists is 0. */
  BrotliDictionary* words_instances;

  /* Amount of custom transform lists. May be 0 if only Brotli's built-in is
     used */
  uint8_t num_transform_lists;

  /* Contents of the custom transform lists. Must be NULL if num_transform_lists
     is 0. */
  BrotliTransforms* transforms_instances;

  /* Concatenated prefix_suffix_maps of the custom transform lists. Must be NULL
     if num_transform_lists is 0. */
  uint16_t* prefix_suffix_maps;

  /* Memory management */
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void* memory_manager_opaque;
};

typedef struct BrotliSharedDictionaryStruct BrotliSharedDictionaryInternal;
#define BrotliSharedDictionary BrotliSharedDictionaryInternal

#if defined(__cplusplus) || defined(c_plusplus)
}  /* extern "C" */
#endif

#endif  /* BROTLI_COMMON_SHARED_DICTIONARY_INTERNAL_H_ */
