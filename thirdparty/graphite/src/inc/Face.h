/**************************************************************************/
/*  Face.h                                                                */
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

#pragma once

#include <cstdio>

#include "graphite2/Font.h"

#include "inc/Main.h"
#include "inc/FeatureMap.h"
#include "inc/TtfUtil.h"
#include "inc/Silf.h"
#include "inc/Error.h"

namespace graphite2 {

class Cmap;
class FileFace;
class GlyphCache;
class NameTable;
class json;
class Font;


using TtfUtil::Tag;

// These are the actual tags, as distinct from the consecutive IDs in TtfUtil.h

class Face
{
    // Prevent any kind of copying
    Face(const Face&);
    Face& operator=(const Face&);

public:
    class Table;
    static float default_glyph_advance(const void* face_ptr, gr_uint16 glyphid);

    Face(const void* appFaceHandle/*non-NULL*/, const gr_face_ops & ops);
    virtual ~Face();

    virtual bool        runGraphite(Segment *seg, const Silf *silf) const;

public:
    bool                readGlyphs(uint32 faceOptions);
    bool                readGraphite(const Table & silf);
    bool                readFeatures();
    void                takeFileFace(FileFace* pFileFace/*takes ownership*/);

    const SillMap     & theSill() const;
    const GlyphCache  & glyphs() const;
    Cmap              & cmap() const;
    NameTable         * nameTable() const;
    void                setLogger(FILE *log_file);
    json              * logger() const throw();

    const Silf        * chooseSilf(uint32 script) const;
    uint16              languageForLocale(const char * locale) const;

    // Features
    uint16              numFeatures() const;
    const FeatureRef  * featureById(uint32 id) const;
    const FeatureRef  * feature(uint16 index) const;

    // Glyph related
    int32  getGlyphMetric(uint16 gid, uint8 metric) const;
    uint16 findPseudo(uint32 uid) const;

    // Errors
    unsigned int        error() const { return m_error; }
    bool                error(Error e) { m_error = e.error(); return false; }
    unsigned int        error_context() const { return m_error; }
    void                error_context(unsigned int errcntxt) { m_errcntxt = errcntxt; }

    CLASS_NEW_DELETE;
private:
    SillMap                 m_Sill;
    gr_face_ops             m_ops;
    const void            * m_appFaceHandle;    // non-NULL
    FileFace              * m_pFileFace;        //owned
    mutable GlyphCache    * m_pGlyphFaceCache;  // owned - never NULL
    mutable Cmap          * m_cmap;             // cmap cache if available
    mutable NameTable     * m_pNames;
    mutable json          * m_logger;
    unsigned int            m_error;
    unsigned int            m_errcntxt;
protected:
    Silf                  * m_silfs;    // silf subtables.
    uint16                  m_numSilf;  // num silf subtables in the silf table
private:
    uint16 m_ascent,
           m_descent;
#ifdef GRAPHITE2_TELEMETRY
public:
    mutable telemetry   tele;
#endif
};



inline
const SillMap & Face::theSill() const
{
    return m_Sill;
}

inline
uint16 Face::numFeatures() const
{
    return m_Sill.theFeatureMap().numFeats();
}

inline
const FeatureRef * Face::featureById(uint32 id) const
{
    return m_Sill.theFeatureMap().findFeatureRef(id);
}

inline
const FeatureRef *Face::feature(uint16 index) const
{
    return m_Sill.theFeatureMap().feature(index);
}

inline
const GlyphCache & Face::glyphs() const
{
    return *m_pGlyphFaceCache;
}

inline
Cmap & Face::cmap() const
{
    return *m_cmap;
};

inline
json * Face::logger() const throw()
{
    return m_logger;
}



class Face::Table
{
    const Face *            _f;
    mutable const byte *    _p;
    size_t                  _sz;
    bool                    _compressed;

    Error decompress();

    void release();

public:
    Table() throw();
    Table(const Face & face, const Tag n, uint32 version=0xffffffff) throw();
    ~Table() throw();
    Table(const Table && rhs) throw();

    operator const byte * () const throw();

    size_t  size() const throw();
    Table & operator = (const Table && rhs) throw();
};

inline
Face::Table::Table() throw()
: _f(0), _p(0), _sz(0), _compressed(false)
{
}

inline
Face::Table::Table(const Table && rhs) throw()
: _f(rhs._f), _p(rhs._p), _sz(rhs._sz), _compressed(rhs._compressed)
{
    rhs._p = 0;
}

inline
Face::Table::~Table() throw()
{
    release();
}

inline
Face::Table::operator const byte * () const throw()
{
    return _p;
}

inline
size_t  Face::Table::size() const throw()
{
    return _sz;
}

} // namespace graphite2

struct gr_face : public graphite2::Face {};
