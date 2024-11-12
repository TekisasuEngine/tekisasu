/**************************************************************************/
/*  clipper.rectclip.h                                                    */
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

* Author    :  Angus Johnson                                                   *
* Date      :  1 November 2023                                                 *
* Website   :  http://www.angusj.com                                           *
* Copyright :  Angus Johnson 2010-2023                                         *
* Purpose   :  FAST rectangular clipping                                       *
* License   :  http://www.boost.org/LICENSE_1_0.txt                            *
*******************************************************************************/

#ifndef CLIPPER_RECTCLIP_H
#define CLIPPER_RECTCLIP_H

#include <cstdlib>
#include <vector>
#include <queue>
#include "clipper2/clipper.core.h"

namespace Clipper2Lib
{

  enum class Location { Left, Top, Right, Bottom, Inside };

  class OutPt2;
  typedef std::vector<OutPt2*> OutPt2List;

  class OutPt2 {
  public:
    Point64 pt;
    size_t owner_idx;
    OutPt2List* edge;
    OutPt2* next;
    OutPt2* prev;
  };

  //------------------------------------------------------------------------------
  // RectClip64
  //------------------------------------------------------------------------------

  class RectClip64 {
  private:
    void ExecuteInternal(const Path64& path);
    Path64 GetPath(OutPt2*& op);
  protected:
    const Rect64 rect_;
    const Path64 rect_as_path_;
    const Point64 rect_mp_;
    Rect64 path_bounds_;
    std::deque<OutPt2> op_container_;
    OutPt2List results_;  // each path can be broken into multiples
    OutPt2List edges_[8]; // clockwise and counter-clockwise
    std::vector<Location> start_locs_;
    void CheckEdges();
    void TidyEdges(int idx, OutPt2List& cw, OutPt2List& ccw);
    void GetNextLocation(const Path64& path,
      Location& loc, int& i, int highI);
    OutPt2* Add(Point64 pt, bool start_new = false);
    void AddCorner(Location prev, Location curr);
    void AddCorner(Location& loc, bool isClockwise);
  public:
    explicit RectClip64(const Rect64& rect) :
      rect_(rect),
      rect_as_path_(rect.AsPath()),
      rect_mp_(rect.MidPoint()) {}
    Paths64 Execute(const Paths64& paths);
  };

  //------------------------------------------------------------------------------
  // RectClipLines64
  //------------------------------------------------------------------------------

  class RectClipLines64 : public RectClip64 {
  private:
    void ExecuteInternal(const Path64& path);
    Path64 GetPath(OutPt2*& op);
  public:
    explicit RectClipLines64(const Rect64& rect) : RectClip64(rect) {};
    Paths64 Execute(const Paths64& paths);
  };

} // Clipper2Lib namespace
#endif  // CLIPPER_RECTCLIP_H
