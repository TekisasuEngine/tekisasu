/**************************************************************************/
/*  version.h                                                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
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

#pragma once

#include "core/version_generated.gen.h" // IWYU pragma: export

#include <stdint.h> // NOLINT(modernize-deprecated-headers) FIXME: MinGW compilation fails when changing to C++ Header.

// Copied from typedefs.h to stay lean.
#ifndef _STR
#define _STR(m_x) #m_x
#define _MKSTR(m_x) _STR(m_x)
#endif

// Tekisasu versions are of the form <major>.<minor> for the initial release,
// and then <major>.<minor>.<patch> for subsequent bugfix releases where <patch> != 0
// That's arbitrary, but we find it pretty and it's the current policy.

// Defines the main "branch" version. Patch versions in this branch should be
// forward-compatible.
// Example: "3.1"
#define TEKISASU_VERSION_BRANCH _MKSTR(TEKISASU_VERSION_MAJOR) "." _MKSTR(TEKISASU_VERSION_MINOR)
#if TEKISASU_VERSION_PATCH
// Example: "3.1.4"
#define TEKISASU_VERSION_NUMBER TEKISASU_VERSION_BRANCH "." _MKSTR(TEKISASU_VERSION_PATCH)
#else // patch is 0, we don't include it in the "pretty" version number.
// Example: "3.1" instead of "3.1.0"
#define TEKISASU_VERSION_NUMBER TEKISASU_VERSION_BRANCH
#endif // TEKISASU_VERSION_PATCH

// Version number encoded as hexadecimal int with one byte for each number,
// for easy comparison from code.
// Example: 3.1.4 will be 0x030104, making comparison easy from script.
#define TEKISASU_VERSION_HEX 0x10000 * TEKISASU_VERSION_MAJOR + 0x100 * TEKISASU_VERSION_MINOR + TEKISASU_VERSION_PATCH

// Describes the full configuration of that Tekisasu version, including the version number,
// the status (beta, stable, etc.), potential module-specific features (e.g. mono)
// and double-precision status.
// Example: "3.1.4.stable.mono.double"
#ifdef REAL_T_IS_DOUBLE
#define TEKISASU_VERSION_FULL_CONFIG TEKISASU_VERSION_NUMBER "." TEKISASU_VERSION_STATUS TEKISASU_VERSION_MODULE_CONFIG ".double"
#else
#define TEKISASU_VERSION_FULL_CONFIG TEKISASU_VERSION_NUMBER "." TEKISASU_VERSION_STATUS TEKISASU_VERSION_MODULE_CONFIG
#endif

// Similar to TEKISASU_VERSION_FULL_CONFIG, but also includes the (potentially custom) TEKISASU_VERSION_BUILD
// description (e.g. official, custom_build, etc.), unless the build is "custom_build" in which case it's omitted.
// Example: "3.1.4.stable.mono.double.official" or "3.1.4.stable.mono.double" (if custom_build)
#define TEKISASU_VERSION_FULL_BUILD TEKISASU_VERSION_FULL_CONFIG TEKISASU_VERSION_BUILD_SUFFIX

// Same as above, but prepended with Tekisasu's name and a cosmetic "v" for "version".
// Example: "Tekisasu v3.1.4.stable.official.mono.double"
#define TEKISASU_VERSION_FULL_NAME TEKISASU_VERSION_NAME " v" TEKISASU_VERSION_FULL_BUILD

// Upstream (Godot) version string. Follows the same pattern as TEKISASU_VERSION_NUMBER:
// omits patch if it's 0, includes it otherwise.
// Example: "4.6.dev" or "4.6.1.dev"
#define TEKISASU_VERSION_UPSTREAM_BRANCH _MKSTR(TEKISASU_VERSION_UPSTREAM_MAJOR) "." _MKSTR(TEKISASU_VERSION_UPSTREAM_MINOR)
#if TEKISASU_VERSION_UPSTREAM_PATCH
#define TEKISASU_VERSION_UPSTREAM_NUMBER TEKISASU_VERSION_UPSTREAM_BRANCH "." _MKSTR(TEKISASU_VERSION_UPSTREAM_PATCH) "." TEKISASU_VERSION_UPSTREAM_STATUS
#else
#define TEKISASU_VERSION_UPSTREAM_NUMBER TEKISASU_VERSION_UPSTREAM_BRANCH "." TEKISASU_VERSION_UPSTREAM_STATUS
#endif

// Git commit hash, generated at build time in `core/version_hash.gen.cpp`.
extern const char *const TEKISASU_VERSION_HASH;

// Git commit date UNIX timestamp (in seconds), generated at build time in `core/version_hash.gen.cpp`.
// Set to 0 if unknown.
extern const uint64_t TEKISASU_VERSION_TIMESTAMP;

// XOR obfuscation key for PCK files, generated at build time in `core/xor_key.gen.cpp`.
extern const int TEKISASU_XOR_KEY_SIZE;
extern const uint8_t tekisasu_xor_key[];

#ifndef DISABLE_DEPRECATED
// Compatibility with pre-4.5 modules.
#define VERSION_SHORT_NAME TEKISASU_VERSION_SHORT_NAME
#define VERSION_NAME TEKISASU_VERSION_NAME
#define VERSION_MAJOR TEKISASU_VERSION_MAJOR
#define VERSION_MINOR TEKISASU_VERSION_MINOR
#define VERSION_PATCH TEKISASU_VERSION_PATCH
#define VERSION_STATUS TEKISASU_VERSION_STATUS
#define VERSION_BUILD TEKISASU_VERSION_BUILD
#define VERSION_MODULE_CONFIG TEKISASU_VERSION_MODULE_CONFIG
#define VERSION_WEBSITE TEKISASU_VERSION_WEBSITE
#define VERSION_DOCS_BRANCH TEKISASU_VERSION_DOCS_BRANCH
#define VERSION_DOCS_URL TEKISASU_VERSION_DOCS_URL
#define VERSION_BRANCH TEKISASU_VERSION_BRANCH
#define VERSION_NUMBER TEKISASU_VERSION_NUMBER
#define VERSION_HEX TEKISASU_VERSION_HEX
#define VERSION_FULL_CONFIG TEKISASU_VERSION_FULL_CONFIG
#define VERSION_FULL_BUILD TEKISASU_VERSION_FULL_BUILD
#define VERSION_FULL_NAME TEKISASU_VERSION_FULL_NAME
#define VERSION_HASH TEKISASU_VERSION_HASH
#define VERSION_TIMESTAMP TEKISASU_VERSION_TIMESTAMP
#endif // DISABLE_DEPRECATED
