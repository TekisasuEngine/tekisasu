/**************************************************************************/
/*  restrace.h                                                            */
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

// © 2019 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

#ifndef __RESTRACE_H__
#define __RESTRACE_H__

#include "unicode/utypes.h"

#if U_ENABLE_TRACING

struct UResourceBundle;

U_NAMESPACE_BEGIN

class CharString;

/**
 * Instances of this class store information used to trace reads from resource
 * bundles when ICU is built with --enable-tracing.
 *
 * All arguments of type const UResourceBundle*, const char*, and
 * const ResourceTracer& are stored as pointers. The caller must retain
 * ownership for the lifetime of this ResourceTracer.
 *
 * Exported as U_COMMON_API for Windows because it is a value field
 * in other exported types.
 */
class U_COMMON_API ResourceTracer {
public:
    ResourceTracer() :
        fResB(nullptr),
        fParent(nullptr),
        fKey(nullptr),
        fIndex(-1) {}

    ResourceTracer(const UResourceBundle* resB) :
        fResB(resB),
        fParent(nullptr),
        fKey(nullptr),
        fIndex(-1) {}

    ResourceTracer(const UResourceBundle* resB, const char* key) :
        fResB(resB),
        fParent(nullptr),
        fKey(key),
        fIndex(-1) {}

    ResourceTracer(const UResourceBundle* resB, int32_t index) :
        fResB(resB),
        fParent(nullptr),
        fKey(nullptr),
        fIndex(index) {}

    ResourceTracer(const ResourceTracer& parent, const char* key) :
        fResB(nullptr),
        fParent(&parent),
        fKey(key),
        fIndex(-1) {}

    ResourceTracer(const ResourceTracer& parent, int32_t index) :
        fResB(nullptr),
        fParent(&parent),
        fKey(nullptr),
        fIndex(index) {}

    ~ResourceTracer();

    void trace(const char* type) const;
    void traceOpen() const;

    /**
     * Calls trace() if the resB or parent provided to the constructor was
     * non-null; otherwise, does nothing.
     */
    void maybeTrace(const char* type) const {
        if (fResB || fParent) {
            trace(type);
        }
    }

private:
    const UResourceBundle* fResB;
    const ResourceTracer* fParent;
    const char* fKey;
    int32_t fIndex;

    CharString& getFilePath(CharString& output, UErrorCode& status) const;

    CharString& getResPath(CharString& output, UErrorCode& status) const;
};

/**
 * This class provides methods to trace data file reads when ICU is built
 * with --enable-tracing.
 */
class FileTracer {
public:
    static void traceOpen(const char* path, const char* type, const char* name);

private:
    static void traceOpenDataFile(const char* path, const char* type, const char* name);
    static void traceOpenResFile(const char* path, const char* name);
};

U_NAMESPACE_END

#else // U_ENABLE_TRACING

U_NAMESPACE_BEGIN

/**
 * Default trivial implementation when --enable-tracing is not used.
 */
class U_COMMON_API ResourceTracer {
public:
    ResourceTracer() {}

    ResourceTracer(const void*) {}

    ResourceTracer(const void*, const char*) {}

    ResourceTracer(const void*, int32_t) {}

    ResourceTracer(const ResourceTracer&, const char*) {}

    ResourceTracer(const ResourceTracer&, int32_t) {}

    void trace(const char*) const {}

    void traceOpen() const {}

    void maybeTrace(const char*) const {}
};

/**
 * Default trivial implementation when --enable-tracing is not used.
 */
class FileTracer {
public:
    static void traceOpen(const char*, const char*, const char*) {}
};

U_NAMESPACE_END

#endif // U_ENABLE_TRACING

#endif //__RESTRACE_H__
