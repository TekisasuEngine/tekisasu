# Backports from Upstream Godot Engine

This file documents patches and features backported from upstream Godot Engine
that are not part of the base Godot 4.3.1 release from which Tekisasu is forked.

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
