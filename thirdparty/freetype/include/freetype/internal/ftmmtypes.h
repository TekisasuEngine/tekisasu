/**************************************************************************/
/*  ftmmtypes.h                                                           */
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

 *
 * ftmmtypes.h
 *
 *   OpenType Variations type definitions for internal use
 *   with the multi-masters service (specification).
 *
 * Copyright (C) 2022-2023 by
 * David Turner, Robert Wilhelm, Werner Lemberg, George Williams, and
 * Dominik Röttsches.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef FTMMTYPES_H_
#define FTMMTYPES_H_

FT_BEGIN_HEADER


  typedef FT_Int32  FT_ItemVarDelta;

  typedef struct  GX_ItemVarDataRec_
  {
    FT_UInt            itemCount;      /* Number of delta sets per item.   */
    FT_UInt            regionIdxCount; /* Number of region indices.        */
    FT_UInt*           regionIndices;  /* Array of `regionCount` indices;  */
                                       /* these index `varRegionList`.     */
    FT_Byte*           deltaSet;       /* Array of `itemCount` deltas;     */
                                       /* use `innerIndex` for this array. */
    FT_UShort          wordDeltaCount; /* Number of the first 32-bit ints  */
                                       /* or 16-bit ints of `deltaSet`     */
                                       /* depending on `longWords`.        */
    FT_Bool            longWords;      /* If true, `deltaSet` is a 32-bit  */
                                       /* array followed by a 16-bit       */
                                       /* array, otherwise a 16-bit array  */
                                       /* followed by an 8-bit array.      */
  } GX_ItemVarDataRec, *GX_ItemVarData;


  /* contribution of one axis to a region */
  typedef struct  GX_AxisCoordsRec_
  {
    FT_Fixed  startCoord;
    FT_Fixed  peakCoord;      /* zero means no effect (factor = 1) */
    FT_Fixed  endCoord;

  } GX_AxisCoordsRec, *GX_AxisCoords;


  typedef struct  GX_VarRegionRec_
  {
    GX_AxisCoords  axisList;               /* array of axisCount records */

  } GX_VarRegionRec, *GX_VarRegion;


  /* item variation store */
  typedef struct  GX_ItemVarStoreRec_
  {
    FT_UInt         dataCount;
    GX_ItemVarData  varData;            /* array of dataCount records;     */
                                        /* use `outerIndex' for this array */
    FT_UShort     axisCount;
    FT_UInt       regionCount;          /* total number of regions defined */
    GX_VarRegion  varRegionList;

  } GX_ItemVarStoreRec, *GX_ItemVarStore;


  typedef struct  GX_DeltaSetIdxMapRec_
  {
    FT_ULong  mapCount;
    FT_UInt*  outerIndex;               /* indices to item var data */
    FT_UInt*  innerIndex;               /* indices to delta set     */

  } GX_DeltaSetIdxMapRec, *GX_DeltaSetIdxMap;


FT_END_HEADER

#endif /* FTMMTYPES_H_ */


/* END */
