/**************************************************************************/
/*  dbus-address.h                                                        */
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

/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-address.h  Server address parser.
 *
 * Copyright (C) 2003  CodeFactory AB
 *
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#if !defined (DBUS_INSIDE_DBUS_H) && !defined (DBUS_COMPILATION)
#error "Only <dbus/dbus.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef DBUS_ADDRESS_H
#define DBUS_ADDRESS_H

#include <dbus/dbus-types.h>
#include <dbus/dbus-errors.h>

DBUS_BEGIN_DECLS

/**
 * @addtogroup DBusAddress
 * @{
 */

/** Opaque type representing one of the semicolon-separated items in an address */
typedef struct DBusAddressEntry DBusAddressEntry;

DBUS_EXPORT
dbus_bool_t dbus_parse_address            (const char         *address,
					   DBusAddressEntry ***entry_result,
					   int                *array_len,
					   DBusError          *error);
DBUS_EXPORT
const char *dbus_address_entry_get_value  (DBusAddressEntry   *entry,
					   const char         *key);
DBUS_EXPORT
const char *dbus_address_entry_get_method (DBusAddressEntry   *entry);
DBUS_EXPORT
void        dbus_address_entries_free     (DBusAddressEntry  **entries);

DBUS_EXPORT
char* dbus_address_escape_value   (const char *value);
DBUS_EXPORT
char* dbus_address_unescape_value (const char *value,
                                   DBusError  *error);

/**
 * Clear a variable or struct member that contains an array of #DBusAddressEntry.
 * If it does not contain #NULL, the entries that were previously
 * there are freed with dbus_address_entries_free().
 *
 * This is similar to dbus_clear_connection(): see that function
 * for more details.
 *
 * @param pointer_to_entries A pointer to a variable or struct member.
 * pointer_to_entries must not be #NULL, but *pointer_to_entries
 * may be #NULL.
 */
static inline void
dbus_clear_address_entries (DBusAddressEntry ***pointer_to_entries)
{
  _dbus_clear_pointer_impl (DBusAddressEntry *, pointer_to_entries,
                            dbus_address_entries_free);
}

/** @} */

DBUS_END_DECLS

#endif /* DBUS_ADDRESS_H */

