/**************************************************************************/
/*  debug.h                                                               */
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

/* ******************************************************************
 * debug
 * Part of FSE library
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * You can contact the author at :
 * - Source repository : https://github.com/Cyan4973/FiniteStateEntropy
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
****************************************************************** */


/*
 * The purpose of this header is to enable debug functions.
 * They regroup assert(), DEBUGLOG() and RAWLOG() for run-time,
 * and DEBUG_STATIC_ASSERT() for compile-time.
 *
 * By default, DEBUGLEVEL==0, which means run-time debug is disabled.
 *
 * Level 1 enables assert() only.
 * Starting level 2, traces can be generated and pushed to stderr.
 * The higher the level, the more verbose the traces.
 *
 * It's possible to dynamically adjust level using variable g_debug_level,
 * which is only declared if DEBUGLEVEL>=2,
 * and is a global variable, not multi-thread protected (use with care)
 */

#ifndef DEBUG_H_12987983217
#define DEBUG_H_12987983217

#if defined (__cplusplus)
extern "C" {
#endif


/* static assert is triggered at compile time, leaving no runtime artefact.
 * static assert only works with compile-time constants.
 * Also, this variant can only be used inside a function. */
#define DEBUG_STATIC_ASSERT(c) (void)sizeof(char[(c) ? 1 : -1])


/* DEBUGLEVEL is expected to be defined externally,
 * typically through compiler command line.
 * Value must be a number. */
#ifndef DEBUGLEVEL
#  define DEBUGLEVEL 0
#endif


/* recommended values for DEBUGLEVEL :
 * 0 : release mode, no debug, all run-time checks disabled
 * 1 : enables assert() only, no display
 * 2 : reserved, for currently active debug path
 * 3 : events once per object lifetime (CCtx, CDict, etc.)
 * 4 : events once per frame
 * 5 : events once per block
 * 6 : events once per sequence (verbose)
 * 7+: events at every position (*very* verbose)
 *
 * It's generally inconvenient to output traces > 5.
 * In which case, it's possible to selectively trigger high verbosity levels
 * by modifying g_debug_level.
 */

#if (DEBUGLEVEL>=1)
#  define ZSTD_DEPS_NEED_ASSERT
#  include "zstd_deps.h"
#else
#  ifndef assert   /* assert may be already defined, due to prior #include <assert.h> */
#    define assert(condition) ((void)0)   /* disable assert (default) */
#  endif
#endif

#if (DEBUGLEVEL>=2)
#  define ZSTD_DEPS_NEED_IO
#  include "zstd_deps.h"
extern int g_debuglevel; /* the variable is only declared,
                            it actually lives in debug.c,
                            and is shared by the whole process.
                            It's not thread-safe.
                            It's useful when enabling very verbose levels
                            on selective conditions (such as position in src) */

#  define RAWLOG(l, ...)                   \
    do {                                   \
        if (l<=g_debuglevel) {             \
            ZSTD_DEBUG_PRINT(__VA_ARGS__); \
        }                                  \
    } while (0)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LINE_AS_STRING TOSTRING(__LINE__)

#  define DEBUGLOG(l, ...)                               \
    do {                                                 \
        if (l<=g_debuglevel) {                           \
            ZSTD_DEBUG_PRINT(__FILE__ ":" LINE_AS_STRING ": " __VA_ARGS__); \
            ZSTD_DEBUG_PRINT(" \n");                     \
        }                                                \
    } while (0)
#else
#  define RAWLOG(l, ...)   do { } while (0)    /* disabled */
#  define DEBUGLOG(l, ...) do { } while (0)    /* disabled */
#endif


#if defined (__cplusplus)
}
#endif

#endif /* DEBUG_H_12987983217 */
