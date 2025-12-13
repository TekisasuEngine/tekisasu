# Backports from Upstream Godot Engine

This file documents patches and features backported from upstream Godot Engine
that are not part of the base Godot 4.3.1 release from which Tekisasu is forked.

## godotengine/godot#111118 - Add Modern Theme for the Editor

**Original PR:** https://github.com/godotengine/godot/pull/111118
**Original Authors:** YeldhamDev, KoBeWi, and other contributors
**Merged in Godot:** 4.4 development branch
**Backported to Tekisasu:** 2025-12-13

### Description

Introduces a new "Modern" theme style for the Godot editor, alongside the existing
"Classic" theme. The Modern theme provides a refreshed, contemporary look with
improved visual hierarchy and updated styling for editor controls and panels.

### Features

- New theme architecture that separates Classic and Modern theme implementations
- `interface/theme/style` editor setting to switch between "Modern" and "Classic" themes
- Modern theme with updated colors, spacing, and control styles
- Theme-specific adjustments for corner radius and relationship line rendering
- Improved theme generation system with modular style population
- DPITexture resource for resolution-independent texture scaling in themes

### Modifications for Tekisasu

The backport required the following adaptations due to differences between
Godot 4.4+ and the Tekisasu codebase (based on Godot 4.3.1):

1. **File Structure:** The theme system was refactored from a monolithic
   `editor_theme_manager.cpp` into separate files:
   - `theme_modern.cpp/.h` - Modern theme implementation
   - `theme_classic.cpp/.h` - Classic theme implementation (original styling)
   - `editor_theme_manager.cpp/.h` - Theme manager and configuration

2. **Header Guards:** Added proper header guards (`#ifndef`/`#define`/`#endif`)
   to new header files for consistency with Tekisasu conventions.

3. **Include Statements:** Ensured proper include ordering with the header file
   included first in each implementation file.

4. **Accent Color Setting:** Retained the existing Tekisasu accent color setting
   and behavior from the original theme system.

### Files Changed

- `editor/themes/theme_modern.cpp` - Modern theme style population (new file)
- `editor/themes/theme_modern.h` - Modern theme class declaration (new file)
- `editor/themes/theme_classic.cpp` - Classic theme style population (new file)
- `editor/themes/theme_classic.h` - Classic theme class declaration (new file)
- `editor/themes/editor_theme_manager.cpp` - Refactored to use separate theme classes
- `editor/themes/editor_theme_manager.h` - Updated with theme configuration structure
- `editor/editor_settings.cpp` - Added `interface/theme/style` setting
- `editor/editor_settings_dialog.cpp` - Theme style setting UI integration
- `editor/project_manager/quick_settings_dialog.cpp` - Quick settings theme integration
- `scene/resources/dpi_texture.cpp` - DPITexture resource implementation (new file)
- `scene/resources/dpi_texture.h` - DPITexture resource declaration (new file)
- `doc/classes/EditorSettings.xml` - Documentation for new theme style setting
- `editor/themes/editor_icons.cpp` - Icon system updates for theme support
- `editor/themes/editor_icons.h` - Icon system header updates
- `editor/editor_audio_buses.cpp` - Theme integration updates

## godotengine/godot#108079 - Add tab menu button to list currently opened scenes

**Original PR:** https://github.com/godotengine/godot/pull/108079
**Original Author:** arkology
**Merged in Godot:** 4.6 development branch (2025-11-14)
**Backported to Tekisasu:** 2025-12-05

### Description

Adds a dropdown menu button next to the scene tabs that displays a list of all
currently opened scenes. This improves usability when many scenes are open and
some tabs are hidden due to space constraints.

### Features

- New MenuButton with "GuiTabMenuHl" icon added to the scene tabs bar
- Dropdown popup menu lists all opened scenes with their icons
- Clicking an item in the list switches to that scene
- Keyboard shortcut: Alt+T to open the scenes list

### Modifications for Tekisasu

The backport required the following adaptations due to differences between
Godot 4.6 and the Tekisasu codebase (based on Godot 4.3.1):

1. **File Location:** In Godot 4.6, the `EditorSceneTabs` class is located in
   `editor/scene/editor_scene_tabs.cpp/.h`. In Tekisasu (Godot 4.3.1), it
   remains in `editor/gui/editor_scene_tabs.cpp/.h`.

2. **API Differences:**
   - Used `set_icon()` instead of `set_button_icon()` (4.6 API) for setting
     the MenuButton icon
   - Used `set_tooltip_text()` with TTR() instead of `set_accessibility_name()`
     with TTRC() as the accessibility API is not available in 4.3.1
   - The shortcut uses `TTR()` instead of `TTRC()` for translation

### Files Changed

- `editor/gui/editor_scene_tabs.h` - Added MenuButton forward declaration,
  scene_list member variable, and _update_scene_list() method declaration
- `editor/gui/editor_scene_tabs.cpp` - Added MenuButton include, icon theming,
  scene list population logic, and button initialization
