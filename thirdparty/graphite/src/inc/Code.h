/**************************************************************************/
/*  Code.h                                                                */
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

// This class represents loaded graphite stack machine code.  It performs
// basic sanity checks, on the incoming code to prevent more obvious problems
// from crashing graphite.
// Author: Tim Eves

#pragma once

#include <cassert>
#include <graphite2/Types.h>
#include "inc/Main.h"
#include "inc/Machine.h"

namespace graphite2 {

class Silf;
class Face;

enum passtype {
    PASS_TYPE_UNKNOWN = 0,
    PASS_TYPE_LINEBREAK,
    PASS_TYPE_SUBSTITUTE,
    PASS_TYPE_POSITIONING,
    PASS_TYPE_JUSTIFICATION
};

namespace vm {

class Machine::Code
{
public:
    enum status_t
    {
        loaded,
        alloc_failed,
        invalid_opcode,
        unimplemented_opcode_used,
        out_of_range_data,
        jump_past_end,
        arguments_exhausted,
        missing_return,
        nested_context_item,
        underfull_stack
    };

private:
    class decoder;

    instr *     _code;
    byte  *     _data;
    size_t      _data_size,
                _instr_count;
    byte        _max_ref;
    mutable status_t _status;
    bool        _constraint,
                _modify,
                _delete;
    mutable bool _own;

    void release_buffers() throw ();
    void failure(const status_t) throw();

public:
    static size_t estimateCodeDataOut(size_t num_bytecodes, int nRules, int nSlots);

    Code() throw();
    Code(bool is_constraint, const byte * bytecode_begin, const byte * const bytecode_end,
         uint8 pre_context, uint16 rule_length, const Silf &, const Face &,
         enum passtype pt, byte * * const _out = 0);
    Code(const Machine::Code &) throw();
    ~Code() throw();

    Code & operator=(const Code &rhs) throw();
    operator bool () const throw()                  { return _code && status() == loaded; }
    status_t      status() const throw()            { return _status; }
    bool          constraint() const throw()        { return _constraint; }
    size_t        dataSize() const throw()          { return _data_size; }
    size_t        instructionCount() const throw()  { return _instr_count; }
    bool          immutable() const throw()         { return !(_delete || _modify); }
    bool          deletes() const throw()           { return _delete; }
    size_t        maxRef() const throw()            { return _max_ref; }
    void          externalProgramMoved(ptrdiff_t) throw();

    int32 run(Machine &m, slotref * & map) const;

    CLASS_NEW_DELETE;
};

inline
size_t  Machine::Code::estimateCodeDataOut(size_t n_bc, int nRules, int nSlots)
{
    // max is: all codes are instructions + 1 for each rule + max tempcopies
    // allocate space for separate maximal code and data then merge them later
    return (n_bc + nRules + nSlots) * sizeof(instr) + n_bc * sizeof(byte);
}


inline Machine::Code::Code() throw()
: _code(0), _data(0), _data_size(0), _instr_count(0), _max_ref(0),
  _status(loaded), _constraint(false), _modify(false), _delete(false),
  _own(false)
{
}

inline Machine::Code::Code(const Machine::Code &obj) throw ()
 :  _code(obj._code),
    _data(obj._data),
    _data_size(obj._data_size),
    _instr_count(obj._instr_count),
    _max_ref(obj._max_ref),
    _status(obj._status),
    _constraint(obj._constraint),
    _modify(obj._modify),
    _delete(obj._delete),
    _own(obj._own)
{
    obj._own = false;
}

inline Machine::Code & Machine::Code::operator=(const Machine::Code &rhs) throw() {
    if (_instr_count > 0)
        release_buffers();
    _code        = rhs._code;
    _data        = rhs._data;
    _data_size   = rhs._data_size;
    _instr_count = rhs._instr_count;
    _status      = rhs._status;
    _constraint  = rhs._constraint;
    _modify      = rhs._modify;
    _delete      = rhs._delete;
    _own         = rhs._own;
    rhs._own = false;
    return *this;
}

inline void Machine::Code::externalProgramMoved(ptrdiff_t dist) throw()
{
    if (_code && !_own)
    {
        _code += dist / signed(sizeof(instr));
        _data += dist;
    }
}

} // namespace vm
} // namespace graphite2
