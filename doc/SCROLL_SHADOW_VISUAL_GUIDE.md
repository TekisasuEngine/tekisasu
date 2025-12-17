# Scroll Shadow Feature - Visual Guide

## How It Works

### State 1: At Top (No Shadow)
```
┌─────────────────────────────────────┐
│ Toolbar / Fixed Header              │ ← Stationary
├─────────────────────────────────────┤
│ ScrollContainer (scroll_pos = 0)    │
│                                     │
│ ┌─────────────────────────────────┐ │
│ │ Item 1                          │ │
│ │ Item 2                          │ │
│ │ Item 3                          │ │ ← Visible Content
│ │ Item 4                          │ │
│ │ Item 5                          │ │
│ └─────────────────────────────────┘ │
│                                     │
│ [More items below, not visible]     │
└─────────────────────────────────────┘

Shadow Visible: NO ❌
Reason: Scroll position is 0 (at top)
```

### State 2: Scrolled Down (Shadow Appears)
```
┌─────────────────────────────────────┐
│ Toolbar / Fixed Header              │ ← Stationary
├─────────────────────────────────────┤
│ ScrollContainer (scroll_pos > 0)    │
│ ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ │ ← Shadow Gradient (8px)
│ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ │    (Dark to transparent)
│ ┌─────────────────────────────────┐ │
│ │ [Item 1, 2, 3 above]           │ │ ← Hidden above
│ │ Item 4                          │ │
│ │ Item 5                          │ │ ← Visible Content
│ │ Item 6                          │ │
│ │ Item 7                          │ │
│ └─────────────────────────────────┘ │
│ [More items below]                  │
└─────────────────────────────────────┘

Shadow Visible: YES ✅
Reason: User scrolled down, content hidden above
Effect: Visual cue that more content exists above
```

## Code Flow

```
User Scrolls Down
      ↓
v_scroll->value changes
      ↓
_scroll_moved() called
      ↓
queue_redraw() (if scroll_shadow_enabled)
      ↓
NOTIFICATION_DRAW triggered
      ↓
Check conditions:
  1. scroll_shadow_enabled == true?
  2. theme_cache.scroll_shadow_style valid?
  3. v_scroll->get_value() > 0?
      ↓
All YES → Draw shadow StyleBox at top
      ↓
Shadow rendered with gradient effect
```

## Shadow Rendering Details

```
┌─────────────────────────────────────┐
│ Panel Border (panel_style)          │
├─────────────────────────────────────┤  ← panel_style offset
│ ▓ ← Shadow starts here (ofs.x, ofs.y)
│ ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ │  ← Height: scroll_shadow_height
│ ░░░░ (gradient via anti-aliasing)   │
│                                     │
│ Content starts here                 │
│                                     │
└─────────────────────────────────────┘

Width Calculation:
shadow_width = container_size.x - panel_min_size.x
This accounts for margins on BOTH sides

Position:
X: ofs.x (left margin of panel)
Y: ofs.y (top margin of panel)
```

## Theme Customization Examples

### Default Theme (Subtle)
```gdscript
var shadow = StyleBoxFlat.new()
shadow.bg_color = Color(0, 0, 0, 0.3)  # 30% opacity
shadow.anti_aliased = true
shadow.aa_size = 2  # 2px gradient
# Result: Subtle, professional shadow
```

### Heavy Shadow (More Visible)
```gdscript
var shadow = StyleBoxFlat.new()
shadow.bg_color = Color(0, 0, 0, 0.6)  # 60% opacity
shadow.anti_aliased = true
shadow.aa_size = 4  # 4px gradient
theme.set_constant("scroll_shadow_height", "ScrollContainer", 12)
# Result: More prominent shadow, higher visibility
```

### Colored Shadow (Creative)
```gdscript
var shadow = StyleBoxFlat.new()
shadow.bg_color = Color(0.2, 0.3, 0.5, 0.4)  # Blue-ish tint
shadow.anti_aliased = true
shadow.aa_size = 3
# Result: Colored shadow matching brand colors
```

## Performance Characteristics

```
Scenario: Scrolling with Shadow Enabled

Frame N:   User scrolls
           ↓
           v_scroll value changes
           ↓
           queue_redraw() called
           ↓
Frame N+1: NOTIFICATION_DRAW
           ↓
           - Draw panel (always)
           - Check shadow conditions (fast)
           - Draw shadow StyleBox (hardware accelerated)
           ↓
           Frame rendered

Cost: ~1 additional StyleBox draw per scroll frame
Impact: Negligible (<1ms on modern hardware)

Scenario: Scrolling with Shadow Disabled

Frame N:   User scrolls
           ↓
           v_scroll value changes
           ↓
           NO queue_redraw() call
           ↓
Frame N+1: Content repositioned by engine
           ↓
           No additional draw calls

Cost: Zero overhead
```

## Integration Patterns

### Pattern 1: Editor Panel
```
┌─────────────────────────────────────┐
│ Panel Title Bar         [X]         │ ← Fixed Toolbar
├─────────────────────────────────────┤
│ ▓▓ (shadow when scrolled)           │
│ ScrollContainer                     │
│   └─ VBoxContainer                  │ ← Scrollable Content
│        ├─ Inspector Item 1          │
│        ├─ Inspector Item 2          │
│        └─ ...                       │
└─────────────────────────────────────┘
```

### Pattern 2: Dialog with Tabs
```
┌─────────────────────────────────────┐
│ Dialog Title                        │
├─────────────────────────────────────┤
│ [Tab 1] [Tab 2] [Tab 3]            │ ← Tab Bar
├─────────────────────────────────────┤
│ ▓▓ (shadow)                         │
│ ScrollContainer (per tab)           │
│   └─ Tab Content                    │
└─────────────────────────────────────┘
```

### Pattern 3: Documentation Viewer
```
┌─────────────────────────────────────┐
│ Search: [____________]   [Search]   │ ← Fixed Search Bar
├─────────────────────────────────────┤
│ ▓▓ (shadow indicates more above)    │
│ ScrollContainer                     │
│   └─ RichTextLabel                  │
│        (Long documentation text)    │
└─────────────────────────────────────┘
```

## Browser/Platform Compatibility

```
Platform          | StyleBox Support | Shadow Works | Notes
------------------|------------------|--------------|------------------
Windows           | ✅ Full          | ✅ Yes       | DirectX/OpenGL
Linux             | ✅ Full          | ✅ Yes       | OpenGL/Vulkan  
macOS             | ✅ Full          | ✅ Yes       | Metal/OpenGL
Web (HTML5)       | ✅ Full          | ✅ Yes       | WebGL
Android           | ✅ Full          | ✅ Yes       | OpenGL ES
iOS               | ✅ Full          | ✅ Yes       | Metal
```

All platforms support StyleBox rendering natively through the engine's
rendering backend, ensuring consistent appearance and performance.

## Testing Checklist

Visual Tests:
- [ ] Shadow appears when scrolling down
- [ ] Shadow disappears when returning to top
- [ ] Shadow width matches content area
- [ ] Shadow is positioned at top edge
- [ ] Gradient is smooth (no banding)

Functional Tests:
- [ ] Toggle property works (enable/disable)
- [ ] Custom theme styles apply correctly
- [ ] Works with various panel configurations
- [ ] Works with RTL layouts
- [ ] DPI scaling handled correctly

Performance Tests:
- [ ] No FPS drop when scrolling with shadow
- [ ] Zero overhead when disabled
- [ ] No memory leaks on toggle

Edge Cases:
- [ ] Content smaller than container (no shadow)
- [ ] Extremely large content (thousands of items)
- [ ] Missing theme properties (graceful fallback)
- [ ] Zero height container
- [ ] Rapid enable/disable toggling

## Common Use Cases

1. **Inspector Panels**: Show when properties scrolled
2. **File Lists**: Indicate more files above current view
3. **Settings Dialogs**: Long option lists with fixed header
4. **Documentation**: Large help text with search bar
5. **Asset Browsers**: Grid views with toolbar
6. **Console Output**: Log viewers with filter bar
7. **Script Lists**: Project scripts with folder tree
8. **Property Editors**: Node properties in scene tree

All benefit from the visual cue that more content exists above.
