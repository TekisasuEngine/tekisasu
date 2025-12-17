# Testing the Scroll Shadow Feature

This directory contains documentation and examples for the ScrollContainer scroll shadow feature.

## Quick Test

To quickly test the feature in the Tekisasu/Godot editor:

### Method 1: Using the Script Editor

1. Build and run the Tekisasu editor
2. Open the Script Editor
3. Create a new script and paste the contents of `scroll_shadow_demo.gd`
4. Attach the script to a Control node in a test scene
5. Run the scene

You should see:
- A scrollable list with 50 items
- A checkbox to toggle the shadow on/off
- The shadow appearing at the top when you scroll down
- A status label showing the current scroll position

### Method 2: Testing in Editor Panels

1. Build the Tekisasu editor with the changes
2. Open any panel with scrollable content (e.g., Inspector, FileSystem dock)
3. The scroll shadow feature can be enabled on these containers via code:

```gdscript
# In editor plugin or theme customization
var scroll = get_inspector().get_scroll_container()
scroll.scroll_shadow_enabled = true
```

### Method 3: C++ Test

Refer to `scroll_shadow_examples.cpp` for various C++ usage patterns.

## Visual Verification

When testing, verify the following:

### Expected Behavior

✅ **Shadow appears**: When scrolling down from the top
✅ **Shadow hidden**: When at the top (scroll position = 0)
✅ **Smooth gradient**: Shadow should fade from dark to transparent
✅ **Proper positioning**: Shadow should be at the very top of the content area
✅ **Dynamic updates**: Shadow should appear/disappear immediately when scrolling
✅ **Toggle works**: Disabling the feature should remove the shadow

### Edge Cases to Test

1. **No scrollable content**: Shadow should not appear when content fits
2. **Very short content**: Shadow should work correctly even with minimal scroll
3. **Rapid scrolling**: Shadow should update smoothly without flickering
4. **Theme changes**: Custom themes should be able to override shadow style
5. **DPI scaling**: Shadow height should scale with editor DPI settings

## Visual Appearance

The default shadow should look like:
```
┌────────────────────────┐
│ [Dark fade to clear]   │ ← Shadow overlay (8px default)
├────────────────────────┤
│  Scrollable Content    │
│                        │
│  [More content...]     │
│                        │
└────────────────────────┘
```

## Performance Testing

To verify performance:

1. Create a ScrollContainer with 1000+ items
2. Enable the scroll shadow
3. Scroll rapidly up and down
4. Monitor FPS (should remain stable)
5. The feature should have minimal impact when disabled

## Cross-Platform Testing

Test on multiple platforms if possible:
- Windows
- Linux
- macOS
- Web (HTML5 export)
- Mobile (if applicable)

The shadow should render consistently across all platforms.

## Customization Testing

Test theme customization:

```gdscript
# Test different shadow intensities
var shadow = StyleBoxFlat.new()
shadow.bg_color = Color(0, 0, 0, 0.2)  # Light
shadow.bg_color = Color(0, 0, 0, 0.6)  # Heavy

# Test different heights
theme.set_constant("scroll_shadow_height", "ScrollContainer", 4)   # Subtle
theme.set_constant("scroll_shadow_height", "ScrollContainer", 16)  # Prominent
```

## Known Limitations

1. **Horizontal scrolling**: Currently only supports vertical scroll shadow
2. **Bottom shadow**: No shadow at bottom when more content below (potential future enhancement)
3. **Animation**: Shadow appears/disappears instantly (no fade animation yet)

## Reporting Issues

If you find any issues:
1. Describe the expected vs actual behavior
2. Include platform and build information
3. Provide steps to reproduce
4. Include screenshots if possible
5. Check if the issue occurs with shadow disabled

## Documentation

- `SCROLL_SHADOW_FEATURE.md` - Complete feature documentation
- `scroll_shadow_demo.gd` - GDScript demo script
- `scroll_shadow_examples.cpp` - C++ usage examples

## Build Instructions

To build Tekisasu with the scroll shadow feature:

```bash
# Standard build (includes the new feature)
scons platform=<your_platform> target=editor

# The feature is included by default in ScrollContainer
# No special build flags required
```

## Integration with Existing Code

The feature is designed to be non-breaking:
- Disabled by default
- Existing ScrollContainers work without changes
- Theme properties have sensible defaults
- Can be enabled selectively per container

This ensures backward compatibility with existing projects and themes.
