/**************************************************************************/
/*  sysman_dock.cpp                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                            TEKISASU ENGINE                             */
/*                       https://dev.tekisasu.com                         */
/**************************************************************************/
/* Copyright (c) 2021-present Tekisasu                                    */
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

#include "sysman_dock.h"

#include "editor/editor_string_names.h"
#include "editor/themes/editor_scale.h"
#include "scene/gui/box_container.h"

void SysmanDock::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_THEME_CHANGED: {
			// Update the connection icon with the GuiSliderGrabber texture
			if (connection_icon) {
				connection_icon->set_texture(get_theme_icon(SNAME("GuiSliderGrabber"), EditorStringName(EditorIcons)));
				// Set red color for disconnected state
				connection_icon->set_modulate(get_theme_color(SNAME("error_color"), EditorStringName(Editor)));
			}

			// Get the default theme font size
			int default_font_size = get_theme_font_size(SceneStringName(font_size), SNAME("Label"));
			// Apply font size - 1 to all labels in the dock
			int sysman_font_size = MAX(default_font_size - 1, 1); // Ensure font size is at least 1

			if (status_label) {
				status_label->add_theme_font_size_override(SceneStringName(font_size), sysman_font_size);
			}
			if (connection_status_label) {
				connection_status_label->add_theme_font_size_override(SceneStringName(font_size), sysman_font_size);
			}
		} break;
	}
}

SysmanDock::SysmanDock() {
	set_name(TTRC("Sysman"));
	set_icon_name("Tekisasu");
	set_default_slot(DockConstants::DOCK_SLOT_LEFT_BR);

	// Create main container aligned to top-left
	main_container = memnew(VBoxContainer);
	main_container->set_v_size_flags(SIZE_SHRINK_BEGIN);
	main_container->set_h_size_flags(SIZE_SHRINK_BEGIN);
	add_child(main_container);

	// Create status container for the horizontal layout
	status_container = memnew(HBoxContainer);
	main_container->add_child(status_container);

	// Add "Status:" label
	status_label = memnew(Label);
	status_label->set_text(TTRC("Status:"));
	status_container->add_child(status_label);

	// Add connection icon (GuiSliderGrabber, will be set in NOTIFICATION_THEME_CHANGED)
	connection_icon = memnew(TextureRect);
	connection_icon->set_expand_mode(TextureRect::EXPAND_FIT_HEIGHT);
	connection_icon->set_stretch_mode(TextureRect::STRETCH_KEEP_ASPECT_CENTERED);
	connection_icon->set_custom_minimum_size(Size2(14, 14));
	connection_icon->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	status_container->add_child(connection_icon);

	// Add "No Connection" text
	connection_status_label = memnew(Label);
	connection_status_label->set_text(TTRC("No Connection"));
	status_container->add_child(connection_status_label);
}
