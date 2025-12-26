# Tekisasu Engine Technical Modifications

This document summarizes the cumulative modifications made to the upstream Godot Engine to create Tekisasu Engine. These modifications represent the current state of changes, not the historical evolution of how they were implemented.

## Version Information

- **Tekisasu Version**: 1.2.0 stable
- **Upstream Godot Version**: 4.6.0 dev
- **Project Website**: https://dev.tekisasu.com

## Core Engine Modifications

### Version and Branding System

**Modified Files**: `version.py`, `core/version.h`, `core/version_generated.gen.h`

- Implemented dual versioning system with separate Tekisasu and upstream Godot version tracking
- Tekisasu versions follow `<major>.<minor>.<patch>` format
- Version macros renamed from `VERSION_*` to `TEKISASU_VERSION_*` for clarity
- Added `TEKISASU_VERSION_UPSTREAM_*` macros to track the upstream Godot version
- Version display format: "Tekisasu v1.2.0.stable.official" with upstream reference "4.6.dev"
- Updated version headers and build system to use "Tekisasu Engine" branding

### Project File Naming

**Modified Files**: `core/config/project_settings.cpp`, `core/variant/variant_parser.cpp`, `editor/project_manager/*`

- Renamed universal project file from `project.godot` to `project.tekisasu`
- Updated all project loading, saving, and validation logic to use new filename
- Maintained backward compatibility checks where appropriate
- Updated project manager and editor references throughout the codebase

### PCK File XOR Obfuscation

**Modified Files**: `core/io/file_access_pack.cpp`, `core/io/pck_packer.cpp`, `core/core_builders.py`, `methods.py`, `version.py`

- Implemented XOR obfuscation system for PCK (packed resource) files
- Added 1024-byte XOR key generation at build time
- XOR key stored in `tekisasu_xor_key` variable in `version.py`
- Generated keys embedded in compiled binary via `core/xor_key.gen.cpp`
- Obfuscation applied to both PCK file headers and asset data
- External declarations in `core/version.h`: `TEKISASU_XOR_KEY_SIZE` and `tekisasu_xor_key[]`

### Engine API Extensions

**Modified Files**: `core/config/engine.cpp`, `core/core_bind.cpp`, `core/core_bind.h`

- Added `Engine.get_teksec()` method for runtime security token access
- Returns string value: `"tekisasu__change_me_for_production_release"`
- Accessible from GDScript/C# via the Engine singleton
- Intended for custom authentication or validation workflows

### HTTP User-Agent

**Modified Files**: Core HTTP client implementation

- Updated HTTP User-Agent string to identify as "TekisasuEngine" with version format
- Helps distinguish Tekisasu traffic from standard Godot traffic in server logs

### Remote Server URLs

**Modified Files**: Editor export, update check, and asset library systems

- Changed default remote server URLs from `godotengine.org` to `dev.tekisasu.com`
- Updated update check endpoints to use Tekisasu infrastructure
- Modified documentation and help links to point to Tekisasu resources

## Editor UI and Theme Modifications

### Theme Color Customization

**Modified Files**: `editor/themes/theme_modern.cpp`, `editor/themes/theme_classic.cpp`, `editor/settings/editor_settings.cpp`

- **Base Color**: Default changed to `Color(0.17, 0.17, 0.20)` - darker slate gray
- **Accent Color**: Default changed to `Color(0.47, 0.55, 0.96)` - periwinkle blue
- **Corner Radius**: Default value set to 3 pixels (stored in `gn_corner_radius`)
- Theme configuration applies these custom colors consistently across the editor
- Colors used for focus highlights, selection states, and UI accents

### Tab Visual Enhancements

**Modified Files**: `editor/themes/theme_modern.cpp`, `editor/editor_node.cpp`

- Added accent color top border to selected tabs for better visual hierarchy
- Applied font color modulation to tab close buttons for proper opacity matching
- Close button opacity now matches text opacity in unselected tabs
- Right button styling also uses font color for consistency
- Updated tab highlight opacity in modern theme

### TekisasuBar - Secondary Toolbar

**Modified Files**: `editor/editor_node.cpp`, `editor/editor_node.h`, `editor/themes/theme_modern.cpp`

- Implemented toggleable secondary toolbar called "TekisasuBar"
- Custom gradient rendering for visual distinction
- Reorganized UI layout to accommodate the new toolbar
- Three-section layout: left, center, and right containers
- Theme variations: `TekisasuBarOuter` and `TekisasuBar`
- Toggle function: `_on_tekisasu_bar_toggle_pressed()`
- Visibility persisted across editor sessions

#### TekisasuBar Components

**System Information Display**:
- Shows runtime system information in the remote debugger session
- Dynamic joypad/gamepad updates
- Performance and hardware monitoring

**Audio Bus Monitor**:
- Top-bar audio bus monitoring controls
- Synchronized mute/solo/bypass state across editor and runtime
- Real-time peak level visualization
- Toggle button to focus or hide the audio dock

**Debug Status Widget**:
- Shows debug client connection status with status icon
- Displays remote client IP address when connected
- Visual indicator for debugging session state

### TitleBarLogo Quick Menu

**Modified Files**: `editor/editor_node.cpp`, `editor/editor_node.h`

- Added always-on quick menu to editor menubar with Tekisasu logo
- Provides fast access to common Tekisasu-specific features
- Custom content and branding integration
- Positioned in the top menu bar for easy access

### Sysman Dock Tab

**Modified Files**: `editor/editor_node.cpp`, `editor/editor_node.h`

- Added "Sysman" dock tab for game manager integration
- Basic UI scaffolding for future system management features
- Provides foundation for Tekisasu-specific workflow tools

### Main Menu Positioning

**Modified Files**: `editor/editor_node.cpp`

- Fixed main menu repositioning when toggling "Collapse Main Menu" setting
- Ensures main menu always appears after quick menu button
- Prevents layout issues during UI reconfiguration

### About Dialog Enhancements

**Modified Files**: `editor/about/about.cpp`, `editor/editor_node.cpp`

- Added "Build" tab to About menu displaying build configuration details
- Shows version information, build date, and configuration flags
- Helps developers verify their Tekisasu build characteristics

### File Dialog Improvements

**Modified Files**: `scene/gui/file_dialog.cpp`

- Prevented file dialog from resetting to executable directory when navigating deep paths
- Maintains user's current directory context during file operations
- Improves workflow when working with nested project structures

### Audio Mixer Debug Fix

**Modified Files**: `editor/debugger/script_editor_debugger.cpp`

- Fixed audio mixer peaks not being displayed during remote debugging
- Corrected data format mismatch in peak transmission
- Ensures proper visualization of audio levels in remote sessions

### AssetLib Visibility

**Modified Files**: `editor/asset_library/asset_library_editor_plugin.cpp`

- Disabled AssetLib visibility by default
- Tekisasu maintains its own asset ecosystem separate from Godot's

## Default Settings and Preferences

### Directory Naming Convention

**Modified Files**: `editor/settings/editor_settings.cpp`

- Changed default directory naming convention to **PascalCase** (value: 4)
- Options: No convention, kebab-case, snake_case, camelCase, PascalCase, Title Case
- Setting path: `project_manager/directory_naming_convention`

### Color Picker Defaults

**Modified Files**: `editor/settings/editor_settings.cpp`

- **Default Mode**: HSV (`ColorPicker::MODE_HSV`)
- **Default Shape**: HSV Rectangle (`ColorPicker::SHAPE_HSV_RECTANGLE`)
- **Show Intensity**: Enabled by default
- Settings paths:
  - `interface/inspector/default_color_picker_mode`
  - `interface/inspector/default_color_picker_shape`
  - `interface/inspector/color_picker_show_intensity`

### Debug Adapter Settings

**Modified Files**: `editor/debugger/debug_adapter/debug_adapter_protocol.h`, `editor/debugger/debug_adapter/debug_adapter_server.cpp`

- **Sync Breakpoints**: Enabled by default (`_sync_breakpoints = true`)
- Automatically synchronizes breakpoints between editor and debug adapter
- Setting path: `network/debug_adapter/sync_breakpoints`

### Debugger Keep Server Open

**Modified Files**: `editor/debugger/debugger_editor_plugin.cpp`

- **Keep Debug Server Open**: Enabled by default
- Debug server remains active after debugging session ends
- Facilitates rapid iteration and testing workflows

### Output Panel Settings

**Modified Files**: `editor/editor_log.cpp`

- **Collapse Duplicate Messages**: Enabled by default (`collapse = true`)
- Reduces visual clutter in the Output panel
- Duplicate consecutive messages are collapsed with a counter

### Font Size Adjustments

**Modified Files**: `editor/themes/theme_modern.cpp`, `editor/themes/theme_classic.cpp`

- Updated help dialog font sizes for better readability
- Optimized text rendering in documentation and about dialogs

## Export and Deployment

### SSH Remote Deploy Fix

**Modified Files**: `editor/export/editor_export_platform.cpp`, platform-specific export implementations

- Fixed SSH remote deploy to properly export and package executables in ZIP format
- Corrected export errors for Windows, LinuxBSD, and macOS platforms
- Ensured executable permissions and file structure preservation

### Export Template Manager

**Modified Files**: `editor/export/export_template_manager.cpp`

- Updated to reference Tekisasu-specific export templates
- Modified download locations to use Tekisasu infrastructure

## Platform-Specific Modifications

### Windows Platform

**Modified Files**: `platform/windows/tekisasu_res.rc`, `platform/windows/tekisasu_res_wrap.rc`, `platform/windows/display_server_windows.cpp`, `platform/windows/detect.py`

- Updated Windows resource files with Tekisasu branding
- Modified application icon and metadata
- Updated copyright and product information in executables

### Linux Platform

**Modified Files**: Distribution XML, appdata.xml, desktop files

- Updated Linux distribution metadata for Tekisasu
- Modified desktop entry files with Tekisasu branding
- Updated appdata for software center integration

## Bug Fixes and Stability

### Reflection Probes

**Modified Files**: Rendering system

- Fixed real-time reflection probes being constantly recreated
- Improved performance and stability of real-time reflections
- Reduced unnecessary GPU overhead

### Shaped Text Substring Clamping

**Modified Files**: Text rendering system

- Clamped shaped text substrings to avoid invalid RIDs
- Prevents crashes in help and about dialogs
- Ensures text rendering stability with complex layouts

### Upstream Integration

**Modified Files**: Various

- Pulled in upstream Godot PR #114259 for compatibility
- Applied upstream Godot PR #113004 for bug fixes
- Maintained regular merges from upstream Godot master branch
- Preserved Tekisasu-specific modifications during upstream merges

## Documentation and Legal

### Copyright and License

**Modified Files**: `COPYRIGHT.txt`, `LICENSE.txt`, `LOGO_LICENSE.txt`, `.mailmap`

- Updated copyright notices to include Tekisasu Engine
- Maintained MIT/Expat license compatibility with upstream Godot
- Updated logo license to reflect Tekisasu proprietary graphics
- Modified contributor attribution files

### Documentation URLs

**Modified Files**: Various help and documentation references

- Updated documentation URLs to point to Tekisasu documentation
- Modified inline help links throughout the editor
- Changed version check and update URLs

## Build System

### Build Configuration

**Modified Files**: `SConstruct`, `methods.py`, `platform_methods.py`, `core/SCsub`, `core/core_builders.py`

- Updated build system to generate Tekisasu-specific version headers
- Integrated XOR key generation into the build process
- Modified project name references throughout SCons build files
- Added Tekisasu-specific build targets and configurations

### Version Hash Generation

**Modified Files**: `core/version_hash.gen.cpp` (generated)

- Build-time generation of git commit hash
- Embeds TEKISASU_VERSION_HASH constant in binary
- Includes commit timestamp for build traceability

## Summary

The Tekisasu Engine represents a comprehensive fork of Godot Engine with:

- **54 unique commits** by or collaborated with Tekisasu-JohnK
- **Custom branding and identity** throughout the engine and editor
- **Enhanced editor UI** with TekisasuBar, custom themes, and improved workflows
- **Security features** including PCK obfuscation and custom API extensions
- **Developer-focused defaults** optimized for the Tekisasu workflow
- **Infrastructure integration** with Tekisasu services and update systems
- **Maintained compatibility** with upstream Godot while adding Tekisasu-specific features

All modifications maintain the MIT/Expat license compatibility with upstream Godot, ensuring the open-source nature of the engine core while supporting Tekisasu's specific requirements and branding.
