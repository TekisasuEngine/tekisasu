/**************************************************************************/
/*  constants.h                                                           */
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

#include "../sys/platform.h"

#include <limits>

#define _USE_MATH_DEFINES
#include <math.h> // using cmath causes issues under Windows
#include <cfloat>
#include <climits>

namespace embree
{
  static MAYBE_UNUSED const float one_over_255 = 1.0f/255.0f;
  static MAYBE_UNUSED const float min_rcp_input = 1E-18f;  // for abs(x) >= min_rcp_input the newton raphson rcp calculation does not fail

  /* we consider floating point numbers in that range as valid input numbers */
  static MAYBE_UNUSED float FLT_LARGE = 1.844E18f;

  struct TrueTy {
    __forceinline operator bool( ) const { return true; }
  };

  const constexpr TrueTy True = TrueTy();

  struct FalseTy {
    __forceinline operator bool( ) const { return false; }
  };

  const constexpr FalseTy False = FalseTy();
  
  struct ZeroTy
  {
    __forceinline operator          double   ( ) const { return 0; }
    __forceinline operator          float    ( ) const { return 0; }
    __forceinline operator          long long( ) const { return 0; }
    __forceinline operator unsigned long long( ) const { return 0; }
    __forceinline operator          long     ( ) const { return 0; }
    __forceinline operator unsigned long     ( ) const { return 0; }
    __forceinline operator          int      ( ) const { return 0; }
    __forceinline operator unsigned int      ( ) const { return 0; }
    __forceinline operator          short    ( ) const { return 0; }
    __forceinline operator unsigned short    ( ) const { return 0; }
    __forceinline operator          char     ( ) const { return 0; }
    __forceinline operator unsigned char     ( ) const { return 0; }
  }; 

  const constexpr ZeroTy zero = ZeroTy();

  struct OneTy
  {
    __forceinline operator          double   ( ) const { return 1; }
    __forceinline operator          float    ( ) const { return 1; }
    __forceinline operator          long long( ) const { return 1; }
    __forceinline operator unsigned long long( ) const { return 1; }
    __forceinline operator          long     ( ) const { return 1; }
    __forceinline operator unsigned long     ( ) const { return 1; }
    __forceinline operator          int      ( ) const { return 1; }
    __forceinline operator unsigned int      ( ) const { return 1; }
    __forceinline operator          short    ( ) const { return 1; }
    __forceinline operator unsigned short    ( ) const { return 1; }
    __forceinline operator          char     ( ) const { return 1; }
    __forceinline operator unsigned char     ( ) const { return 1; }
  };

  const constexpr OneTy one = OneTy();

  struct NegInfTy
  {
    __forceinline operator          double   ( ) const { return -std::numeric_limits<double>::infinity(); }
    __forceinline operator          float    ( ) const { return -std::numeric_limits<float>::infinity(); }
    __forceinline operator          long long( ) const { return std::numeric_limits<long long>::min(); }
    __forceinline operator unsigned long long( ) const { return std::numeric_limits<unsigned long long>::min(); }
    __forceinline operator          long     ( ) const { return std::numeric_limits<long>::min(); }
    __forceinline operator unsigned long     ( ) const { return std::numeric_limits<unsigned long>::min(); }
    __forceinline operator          int      ( ) const { return std::numeric_limits<int>::min(); }
    __forceinline operator unsigned int      ( ) const { return std::numeric_limits<unsigned int>::min(); }
    __forceinline operator          short    ( ) const { return std::numeric_limits<short>::min(); }
    __forceinline operator unsigned short    ( ) const { return std::numeric_limits<unsigned short>::min(); }
    __forceinline operator          char     ( ) const { return std::numeric_limits<char>::min(); }
    __forceinline operator unsigned char     ( ) const { return std::numeric_limits<unsigned char>::min(); }

  };

  const constexpr NegInfTy neg_inf = NegInfTy();

  struct PosInfTy
  {
    __forceinline operator          double   ( ) const { return std::numeric_limits<double>::infinity(); }
    __forceinline operator          float    ( ) const { return std::numeric_limits<float>::infinity(); }
    __forceinline operator          long long( ) const { return std::numeric_limits<long long>::max(); }
    __forceinline operator unsigned long long( ) const { return std::numeric_limits<unsigned long long>::max(); }
    __forceinline operator          long     ( ) const { return std::numeric_limits<long>::max(); }
    __forceinline operator unsigned long     ( ) const { return std::numeric_limits<unsigned long>::max(); }
    __forceinline operator          int      ( ) const { return std::numeric_limits<int>::max(); }
    __forceinline operator unsigned int      ( ) const { return std::numeric_limits<unsigned int>::max(); }
    __forceinline operator          short    ( ) const { return std::numeric_limits<short>::max(); }
    __forceinline operator unsigned short    ( ) const { return std::numeric_limits<unsigned short>::max(); }
    __forceinline operator          char     ( ) const { return std::numeric_limits<char>::max(); }
    __forceinline operator unsigned char     ( ) const { return std::numeric_limits<unsigned char>::max(); }
  };

  const constexpr PosInfTy     inf = PosInfTy();
  const constexpr PosInfTy pos_inf = PosInfTy();

  struct NaNTy
  {
    __forceinline operator double( ) const { return std::numeric_limits<double>::quiet_NaN(); }
    __forceinline operator float ( ) const { return std::numeric_limits<float>::quiet_NaN(); }
  };

  const constexpr NaNTy nan = NaNTy();

  struct UlpTy
  {
    __forceinline operator double( ) const { return std::numeric_limits<double>::epsilon(); }
    __forceinline operator float ( ) const { return std::numeric_limits<float>::epsilon(); }
  };
  
  const constexpr UlpTy ulp = UlpTy();

  struct PiTy
  {
    __forceinline operator double( ) const { return double(M_PI); }
    __forceinline operator float ( ) const { return float(M_PI); }
  };

  const constexpr PiTy pi = PiTy();

  struct OneOverPiTy
  {
    __forceinline operator double( ) const { return double(M_1_PI); }
    __forceinline operator float ( ) const { return float(M_1_PI); }
  };

  const constexpr OneOverPiTy one_over_pi = OneOverPiTy();

  struct TwoPiTy
  {
    __forceinline operator double( ) const { return double(2.0*M_PI); }
    __forceinline operator float ( ) const { return float(2.0*M_PI); }
  };

  const constexpr TwoPiTy two_pi = TwoPiTy();

  struct OneOverTwoPiTy
  {
    __forceinline operator double( ) const { return double(0.5*M_1_PI); }
    __forceinline operator float ( ) const { return float(0.5*M_1_PI); }
  };

  const constexpr OneOverTwoPiTy one_over_two_pi = OneOverTwoPiTy();

  struct FourPiTy
  {
    __forceinline operator double( ) const { return double(4.0*M_PI); } 
    __forceinline operator float ( ) const { return float(4.0*M_PI); }
  };

  const constexpr FourPiTy four_pi = FourPiTy();

  struct OneOverFourPiTy
  {
    __forceinline operator double( ) const { return double(0.25*M_1_PI); }
    __forceinline operator float ( ) const { return float(0.25*M_1_PI); }
  };

  const constexpr OneOverFourPiTy one_over_four_pi = OneOverFourPiTy();

  struct StepTy {
    __forceinline operator          double   ( ) const { return 0; }
    __forceinline operator          float    ( ) const { return 0; }
    __forceinline operator          long long( ) const { return 0; }
    __forceinline operator unsigned long long( ) const { return 0; }
    __forceinline operator          long     ( ) const { return 0; }
    __forceinline operator unsigned long     ( ) const { return 0; }
    __forceinline operator          int      ( ) const { return 0; }
    __forceinline operator unsigned int      ( ) const { return 0; }
    __forceinline operator          short    ( ) const { return 0; }
    __forceinline operator unsigned short    ( ) const { return 0; }
    __forceinline operator          char     ( ) const { return 0; }
    __forceinline operator unsigned char     ( ) const { return 0; }
  };

  const constexpr StepTy step = StepTy();

  struct ReverseStepTy {
  };

  const constexpr ReverseStepTy reverse_step = ReverseStepTy();

  struct EmptyTy {
  };

  const constexpr EmptyTy empty = EmptyTy();

  struct FullTy {
  };

  const constexpr FullTy full = FullTy();

  struct UndefinedTy {
  };

  const constexpr UndefinedTy undefined = UndefinedTy();
}
