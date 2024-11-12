/**************************************************************************/
/*  gr_features.cpp                                                       */
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

// SPDX-License-Identifier: MIT OR MPL-2.0 OR LGPL-2.1-or-later OR GPL-2.0-or-later
// Copyright 2010, SIL International, All rights reserved.

#include "graphite2/Font.h"
#include "inc/Face.h"
#include "inc/FeatureMap.h"
#include "inc/FeatureVal.h"
#include "inc/NameTable.h"

using namespace graphite2;

extern "C" {


gr_uint16 gr_fref_feature_value(const gr_feature_ref* pfeatureref, const gr_feature_val* feats)    //returns 0 if either pointer is NULL
{
    if (!pfeatureref || !feats) return 0;

    return pfeatureref->getFeatureVal(*feats);
}


int gr_fref_set_feature_value(const gr_feature_ref* pfeatureref, gr_uint16 val, gr_feature_val* pDest)
{
    if (!pfeatureref || !pDest) return 0;

    return pfeatureref->applyValToFeature(val, *pDest);
}


gr_uint32 gr_fref_id(const gr_feature_ref* pfeatureref)    //returns 0 if pointer is NULL
{
  if (!pfeatureref)
    return 0;

  return pfeatureref->getId();
}


gr_uint16 gr_fref_n_values(const gr_feature_ref* pfeatureref)
{
    if(!pfeatureref)
        return 0;
    return pfeatureref->getNumSettings();
}


gr_int16 gr_fref_value(const gr_feature_ref* pfeatureref, gr_uint16 settingno)
{
    if(!pfeatureref || (settingno >= pfeatureref->getNumSettings()))
    {
        return 0;
    }
    return pfeatureref->getSettingValue(settingno);
}


void* gr_fref_label(const gr_feature_ref* pfeatureref, gr_uint16 *langId, gr_encform utf, gr_uint32 *length)
{
    if(!pfeatureref)
    {
        langId = 0;
        length = 0;
        return NULL;
    }
    uint16 label = pfeatureref->getNameId();
    NameTable * names = pfeatureref->getFace().nameTable();
    if (!names)
    {
        langId = 0;
        length = 0;
        return NULL;
    }
    return names->getName(*langId, label, utf, *length);
}


void* gr_fref_value_label(const gr_feature_ref*pfeatureref, gr_uint16 setting,
    gr_uint16 *langId, gr_encform utf, gr_uint32 *length)
{
    if(!pfeatureref || (setting >= pfeatureref->getNumSettings()))
    {
        langId = 0;
        length = 0;
        return NULL;
    }
    uint16 label = pfeatureref->getSettingName(setting);
    NameTable * names = pfeatureref->getFace().nameTable();
    if (!names)
    {
        langId = 0;
        length = 0;
        return NULL;
    }
    return names->getName(*langId, label, utf, *length);
}


void gr_label_destroy(void * label)
{
    free(label);
}

gr_feature_val* gr_featureval_clone(const gr_feature_val* pfeatures/*may be NULL*/)
{                      //When finished with the Features, call features_destroy
    return static_cast<gr_feature_val*>(pfeatures ? new Features(*pfeatures) : new Features);
}

void gr_featureval_destroy(gr_feature_val *p)
{
    delete static_cast<Features*>(p);
}


} // extern "C"
