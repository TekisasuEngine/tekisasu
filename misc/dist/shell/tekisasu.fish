# Fish completion for the Godot editor
# To use it, install this file in `~/.config/fish/completions` then restart your shell.
# You can also `source` this file directly in your shell startup file.
#
# Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md).
# Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

function tekisasu_rendering_method_args
    # Use a function instead of a fixed string to customize the argument descriptions.
    echo -e "forward_plus\tHigh-end desktop renderer"
    echo -e "mobile\tHigh-end mobile/desktop renderer"
    echo -e "gl_compatibility\tLow-end desktop, mobile and web renderer"
end

function tekisasu_rendering_driver_args
    # Use a function instead of a fixed string to customize the argument descriptions.
    echo -e "vulkan\tVulkan renderer"
    echo -e "opengl3\tOpenGL ES 3.0 renderer"
    echo -e "dummy\tDummy renderer"
end

# Erase existing completions for Godot.
complete -c tekisasu -e

# General options:
complete -c tekisasu -s h -l help -d "Display the full help message"
complete -c tekisasu -l version -d "Display the version string"
complete -c tekisasu -s v -l verbose -d "Use verbose stdout mode"
complete -c tekisasu -s q -l quiet -d "Quiet mode, silences stdout messages (errors are still displayed)"

# Run options:
complete -c tekisasu -s e -l editor -d "Start the editor instead of running the scene"
complete -c tekisasu -s p -l project-manager -d "Start the project manager, even if a project is auto-detected"
complete -c tekisasu -l debug-server -d "Start the editor debug server (<protocol>://<host/IP>[:<port>] address)" -x
complete -c tekisasu -l quit -d "Quit after the first iteration"
complete -c tekisasu -s l -l language -d "Use a specific locale (<locale> being a two-letter code)" -x
complete -c tekisasu -l path -d "Path to a project (<directory> must contain a 'project.godot' file)" -r
complete -c tekisasu -s u -l upwards -d "Scan folders upwards for project.tekisasu file"
complete -c tekisasu -l main-pack -d "Path to a pack (.pck) file to load" -r
complete -c tekisasu -l render-thread -d "Set the render thread mode" -x -a "unsafe safe separate"
complete -c tekisasu -l remote-fs -d "Use a remote filesystem (<host/IP>[:<port>] address)" -x
complete -c tekisasu -l remote-fs-password -d "Password for remote filesystem" -x
complete -c tekisasu -l audio-driver -d "Set the audio driver" -x
complete -c tekisasu -l audio-output-latency -d "Override audio output latency in milliseconds (default is 15 ms)" -x
complete -c tekisasu -l display-driver -d "Set the display driver" -x
complete -c tekisasu -l rendering-method -d "Set the renderer" -x -a "(tekisasu_rendering_method_args)"
complete -c tekisasu -l rendering-driver -d "Set the rendering driver" -x -a "(tekisasu_rendering_driver_args)"
complete -c tekisasu -l gpu-index -d "Use a specific GPU (run with --verbose to get available device list)" -x
complete -c tekisasu -l text-driver -d "Set the text driver" -x
complete -c tekisasu -l tablet-driver -d "Set the pen tablet input driver" -x
complete -c tekisasu -l headless -d "Enable headless mode (--display-driver headless --audio-driver Dummy). Useful for servers and with --script"
complete -c tekisasu -l log-file -d "Write output/error log to the specified path instead of the default location defined by the project" -x
complete -c tekisasu -l write-movie -d "Write a video to the specified path (usually with .avi or .png extension). --fixed-fps is forced when enabled" -x

# Display options:
complete -c tekisasu -s f -l fullscreen -d "Request fullscreen mode"
complete -c tekisasu -s m -l maximized -d "Request a maximized window"
complete -c tekisasu -s w -l windowed -d "Request windowed mode"
complete -c tekisasu -s t -l always-on-top -d "Request an always-on-top window"
complete -c tekisasu -l resolution -d "Request window resolution" -x
complete -c tekisasu -l position -d "Request window position" -x
complete -c tekisasu -l single-window -d "Use a single window (no separate subwindows)"
complete -c tekisasu -l xr-mode -d "Select Extended Reality (XR) mode" -a "default off on"

# Debug options:
complete -c tekisasu -s d -l debug -d "Debug (local stdout debugger)"
complete -c tekisasu -s b -l breakpoints -d "Specify the breakpoint list as source::line comma-separated pairs, no spaces (use %20 instead)" -x
complete -c tekisasu -l profiling -d "Enable profiling in the script debugger"
complete -c tekisasu -l gpu-profile -d "Show a GPU profile of the tasks that took the most time during frame rendering"
complete -c tekisasu -l gpu-validation -d "Enable graphics API validation layers for debugging"
complete -c tekisasu -l gpu-abort -d "Abort on graphics API usage errors (usually validation layer errors)"
complete -c tekisasu -l remote-debug -d "Enable remote debugging"
complete -c tekisasu -l debug-collisions -d "Show collision shapes when running the scene"
complete -c tekisasu -l debug-navigation -d "Show navigation polygons when running the scene"
complete -c tekisasu -l debug-stringnames -d "Print all StringName allocations to stdout when the engine quits"
complete -c tekisasu -l max-fps -d "Set a maximum number of frames per second rendered (can be used to limit power usage), a value of 0 results in unlimited framerate" -x
complete -c tekisasu -l frame-delay -d "Simulate high CPU load (delay each frame by the given number of milliseconds)" -x
complete -c tekisasu -l time-scale -d "Force time scale (higher values are faster, 1.0 is normal speed)" -x
complete -c tekisasu -l disable-render-loop -d "Disable render loop so rendering only occurs when called explicitly from script"
complete -c tekisasu -l disable-crash-handler -d "Disable crash handler when supported by the platform code"
complete -c tekisasu -l fixed-fps -d "Force a fixed number of frames per second (this setting disables real-time synchronization)" -x
complete -c tekisasu -l print-fps -d "Print the frames per second to the stdout"

# Standalone tools:
complete -c tekisasu -s s -l script -d "Run a script" -r
complete -c tekisasu -l check-only -d "Only parse for errors and quit (use with --script)"
complete -c tekisasu -l export-release -d "Export the project in release mode using the given preset and output path" -x
complete -c tekisasu -l export-debug -d "Export the project in debug mode using the given preset and output path" -x
complete -c tekisasu -l export-pack -d "Export the project data only as a PCK or ZIP file using the given preset and output path" -x
complete -c tekisasu -l convert-3to4 -d "Converts project from Godot 3.x to Godot 4.x"
complete -c tekisasu -l validate-conversion-3to4 -d "Shows what elements will be renamed when converting project from Godot 3.x to Godot 4.x"
complete -c tekisasu -l doctool -d "Dump the engine API reference to the given path in XML format, merging if existing files are found" -r
complete -c tekisasu -l no-docbase -d "Disallow dumping the base types (used with --doctool)"
complete -c tekisasu -l build-solutions -d "Build the scripting solutions (e.g. for C# projects)"
complete -c tekisasu -l dump-gdextension-interface -d "Generate GDExtension header file 'gdextension_interface.h' in the current folder. This file is the base file required to implement a GDExtension"
complete -c tekisasu -l dump-extension-api -d "Generate JSON dump of the Godot API for GDExtension bindings named 'extension_api.json' in the current folder"
complete -c tekisasu -l benchmark -d "Benchmark the run time and print it to console"
complete -c tekisasu -l benchmark-file -d "Benchmark the run time and save it to a given file in JSON format" -x
complete -c tekisasu -l test -d "Run all unit tests; run with '--test --help' for more information" -x
