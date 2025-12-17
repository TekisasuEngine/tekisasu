# Scroll Shadow Feature for ScrollContainer

## Overview

The scroll shadow feature provides enhanced visual cueing for scrollable content areas in the editor UI. When enabled, a subtle drop-down shadow appears at the top of a ScrollContainer, indicating that there is more content above the currently visible area.

## Usage

### Enabling the Feature

To enable the scroll shadow effect on a ScrollContainer:

**Via GDScript:**
```gdscript
var scroll_container = ScrollContainer.new()
scroll_container.scroll_shadow_enabled = true
```

**Via C++:**
```cpp
ScrollContainer *scroll_container = memnew(ScrollContainer);
scroll_container->set_scroll_shadow_enabled(true);
```

### Customizing the Shadow Appearance

The shadow appearance can be customized through the theme system:

```gdscript
# Create a custom shadow style
var shadow_style = StyleBoxFlat.new()
shadow_style.set_bg_color(Color(0, 0, 0, 0.4))  # Darker shadow
shadow_style.set_anti_aliased(true)
shadow_style.set_aa_size(3)  # Wider gradient

# Apply to theme
var theme = Theme.new()
theme.set_stylebox("scroll_shadow_style", "ScrollContainer", shadow_style)
theme.set_constant("scroll_shadow_height", "ScrollContainer", 12)  # Taller shadow
```

## Implementation Details

### How It Works

1. **Detection**: The shadow is displayed whenever the feature is enabled and a valid shadow style exists
2. **Drawing**: A StyleBox is drawn at the top of the scrollable area using the configured `scroll_shadow_style`
3. **Performance**: The shadow only triggers a redraw when the scroll position changes and the feature is enabled

### Browser Compatibility

The feature uses standard Godot/Tekisasu rendering primitives (StyleBox), ensuring compatibility across all platforms:
- Windows
- macOS
- Linux
- Web (HTML5 export)
- Mobile platforms

### Variable Toolbar Heights

The shadow is positioned relative to the panel style's offset, automatically adapting to:
- Different toolbar heights
- Custom panel margins
- Various container configurations

### Edge Cases Handled

1. **No scroll needed**: Shadow not shown when content fits within visible area
2. **Disabled state**: No performance impact when feature is disabled
3. **Missing theme**: Gracefully handles missing shadow style in theme

## Theme Properties

### StyleBox Properties

**`scroll_shadow_style`**: The StyleBox used to draw the shadow overlay
- Default: Semi-transparent black gradient (Color(0, 0, 0, 0.3))
- Recommended: Use StyleBoxFlat with anti-aliasing for smooth gradient
- Can be customized per theme or per control

### Constant Properties

**`scroll_shadow_height`**: Height of the shadow in pixels
- Default: 8 pixels (scaled by EDSCALE)
- Typical range: 6-16 pixels
- Affects how far the shadow extends into the content area

## Example Use Cases

### Editor Panels
```gdscript
# Inspector panel with scroll shadow
var inspector = EditorInspector.new()
inspector.get_scroll_container().scroll_shadow_enabled = true
```

### Custom Dialogs
```gdscript
# Settings dialog with long content list
var dialog = AcceptDialog.new()
var scroll = ScrollContainer.new()
scroll.scroll_shadow_enabled = true
# Add content to scroll container...
dialog.add_child(scroll)
```

### Documentation Viewer
```gdscript
# Help browser with shadow cue
var help_browser = RichTextLabel.new()
var scroll_container = ScrollContainer.new()
scroll_container.scroll_shadow_enabled = true
scroll_container.add_child(help_browser)
```

## Performance Considerations

- **Minimal overhead**: Only redraws when scroll position changes
- **Optional feature**: Enabled by default but can be disabled per use case
- **Efficient rendering**: Uses hardware-accelerated StyleBox rendering
- **No scripting required**: Pure C++ implementation for optimal performance

## Future Enhancements

Potential improvements for future versions:
- Fade animation when shadow appears/disappears
- Bottom shadow for scrollable content that extends below
- Horizontal scroll shadows for horizontally scrollable content
- Configurable shadow intensity based on scroll distance

## Related Classes

- `ScrollContainer`: Main container class with scroll shadow feature
- `StyleBoxFlat`: Used for creating gradient shadow effects
- `VScrollBar`: Vertical scrollbar used for scroll position detection
- `Theme`: System for customizing shadow appearance

## Contributing

When modifying this feature:
1. Maintain backward compatibility (feature enabled by default, but still user-configurable)
2. Test on multiple platforms
3. Ensure theme customization works correctly
4. Update this documentation for any API changes
5. Consider performance impact of rendering changes
