/**************************************************************************/
/*  vhacdRaycastMesh.h                                                    */
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

#ifndef RAYCAST_MESH_H

#define RAYCAST_MESH_H

#include <stdint.h>

namespace VHACD
{

    // Very simple brute force raycast against a triangle mesh.  Tests every triangle; no hierachy.
    // Does a deep copy, always does calculations with full double float precision
    class RaycastMesh
    {
    public:
        static RaycastMesh * createRaycastMesh(uint32_t vcount,		// The number of vertices in the source triangle mesh
            const double *vertices,		// The array of vertex positions in the format x1,y1,z1..x2,y2,z2.. etc.
            uint32_t tcount,		// The number of triangles in the source triangle mesh
            const uint32_t *indices); // The triangle indices in the format of i1,i2,i3 ... i4,i5,i6, ...

        static RaycastMesh * createRaycastMesh(uint32_t vcount,		// The number of vertices in the source triangle mesh
            const float *vertices,		// The array of vertex positions in the format x1,y1,z1..x2,y2,z2.. etc.
            uint32_t tcount,		// The number of triangles in the source triangle mesh
            const uint32_t *indices); // The triangle indices in the format of i1,i2,i3 ... i4,i5,i6, ...


        virtual bool raycast(const double *from,			// The starting point of the raycast
            const double *to,				// The ending point of the raycast
            const double *closestToPoint,	// The point to match the nearest hit location (can just be the 'from' location of no specific point)
            double *hitLocation,			// The point where the ray hit nearest to the 'closestToPoint' location
            double *hitDistance) = 0;		// The distance the ray traveled to the hit location

        virtual void release(void) = 0;
    protected:
        virtual ~RaycastMesh(void) { };
    };

} // end of VHACD namespace

#endif
