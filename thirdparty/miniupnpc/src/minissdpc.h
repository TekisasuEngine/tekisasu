/**************************************************************************/
/*  minissdpc.h                                                           */
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

/* $Id: minissdpc.h,v 1.6 2015/09/18 12:45:16 nanard Exp $ */
/* Project: miniupnp
 * http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/
 * Author: Thomas Bernard
 * Copyright (c) 2005-2015 Thomas Bernard
 * This software is subjects to the conditions detailed
 * in the LICENCE file provided within this distribution */
#ifndef MINISSDPC_H_INCLUDED
#define MINISSDPC_H_INCLUDED

#include "miniupnpc_declspec.h"
#include "upnpdev.h"

/* error codes : */
#define MINISSDPC_SUCCESS (0)
#define MINISSDPC_UNKNOWN_ERROR (-1)
#define MINISSDPC_SOCKET_ERROR (-101)
#define MINISSDPC_MEMORY_ERROR (-102)
#define MINISSDPC_INVALID_INPUT (-103)
#define MINISSDPC_INVALID_SERVER_REPLY (-104)

#ifdef __cplusplus
extern "C" {
#endif

#if !(defined(_WIN32) || defined(__amigaos__) || defined(__amigaos4__))

MINIUPNP_LIBSPEC struct UPNPDev *
getDevicesFromMiniSSDPD(const char * devtype, const char * socketpath, int * error);

MINIUPNP_LIBSPEC int
connectToMiniSSDPD(const char * socketpath);

MINIUPNP_LIBSPEC int
disconnectFromMiniSSDPD(int s);

MINIUPNP_LIBSPEC int
requestDevicesFromMiniSSDPD(int s, const char * devtype);

MINIUPNP_LIBSPEC struct UPNPDev *
receiveDevicesFromMiniSSDPD(int s, int * error);

#endif /* !(defined(_WIN32) || defined(__amigaos__) || defined(__amigaos4__)) */

MINIUPNP_LIBSPEC struct UPNPDev *
ssdpDiscoverDevices(const char * const deviceTypes[],
                    int delay, const char * multicastif,
                    int localport,
                    int ipv6, unsigned char ttl,
                    int * error,
                    int searchalltypes);

#ifdef __cplusplus
}
#endif

#endif

