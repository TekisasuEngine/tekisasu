/*
 * Example C++ code demonstrating the ScrollContainer scroll shadow feature
 * This shows how to enable and customize the scroll shadow effect in C++
 */

#include "scene/gui/scroll_container.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"
#include "scene/gui/button.h"
#include "scene/resources/style_box_flat.h"

// Example 1: Basic usage - Enable scroll shadow with default theme
void example_basic_scroll_shadow() {
	ScrollContainer *scroll = memnew(ScrollContainer);
	
	// Enable the scroll shadow effect
	scroll->set_scroll_shadow_enabled(true);
	
	// Add scrollable content
	VBoxContainer *content = memnew(VBoxContainer);
	scroll->add_child(content);
	
	// Add many items to make it scrollable
	for (int i = 0; i < 50; i++) {
		Button *button = memnew(Button);
		button->set_text("Item " + itos(i + 1));
		button->set_custom_minimum_size(Size2(0, 40));
		content->add_child(button);
	}
}

// Example 2: Custom shadow style
void example_custom_shadow_style(ScrollContainer *scroll, Theme *theme) {
	// Create a custom shadow style with stronger effect
	Ref<StyleBoxFlat> custom_shadow = memnew(StyleBoxFlat);
	
	// Set shadow color (darker for more visibility)
	custom_shadow->set_bg_color(Color(0, 0, 0, 0.5));
	
	// Enable anti-aliasing for smooth gradient
	custom_shadow->set_anti_aliased(true);
	custom_shadow->set_aa_size(4); // Wider gradient
	
	// No borders or margins needed for shadow overlay
	custom_shadow->set_border_width_all(0);
	custom_shadow->set_expand_margin_all(0);
	custom_shadow->set_draw_center(true);
	
	// Apply to theme
	theme->set_stylebox("scroll_shadow_style", "ScrollContainer", custom_shadow);
	theme->set_constant("scroll_shadow_height", "ScrollContainer", 12); // Taller shadow
	
	// Enable the feature
	scroll->set_scroll_shadow_enabled(true);
}

// Example 3: Dynamic toggle based on content
void example_dynamic_shadow_toggle(ScrollContainer *scroll) {
	VScrollBar *vscroll = scroll->get_v_scroll_bar();
	
	// Get the maximum scroll range
	float max_scroll = vscroll->get_max() - vscroll->get_page();
	
	// Only enable shadow if content is actually scrollable
	bool is_scrollable = max_scroll > 0;
	scroll->set_scroll_shadow_enabled(is_scrollable);
}

// Example 4: Monitor scroll position
void example_monitor_scroll_position(ScrollContainer *scroll) {
	VScrollBar *vscroll = scroll->get_v_scroll_bar();
	
	// Connect to scroll changes
	vscroll->connect("value_changed", callable_mp_lambda([scroll, vscroll](float value) {
		// Shadow visibility follows the feature toggle
		bool shadow_visible = scroll->is_scroll_shadow_enabled();
		
		// Log for debugging
		print_line(vformat("Scroll position: %d, Shadow visible: %s", 
			(int)value, 
			shadow_visible ? "Yes" : "No"));
	}));
}

// Example 5: Complete editor panel setup
void example_editor_panel_with_shadow() {
	// Create a panel for editor UI
	PanelContainer *panel = memnew(PanelContainer);
	panel->set_custom_minimum_size(Size2(400, 600));
	
	VBoxContainer *layout = memnew(VBoxContainer);
	panel->add_child(layout);
	
	// Add a fixed toolbar at the top
	HBoxContainer *toolbar = memnew(HBoxContainer);
	toolbar->set_custom_minimum_size(Size2(0, 40));
	layout->add_child(toolbar);
	
	Label *title = memnew(Label);
	title->set_text("My Editor Panel");
	toolbar->add_child(title);
	
	// Add scrollable content area with shadow
	ScrollContainer *scroll = memnew(ScrollContainer);
	scroll->set_scroll_shadow_enabled(true);
	scroll->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	layout->add_child(scroll);
	
	// Add content to scroll area
	VBoxContainer *content = memnew(VBoxContainer);
	scroll->add_child(content);
	
	// The shadow will appear above the content when the feature is enabled
	for (int i = 0; i < 100; i++) {
		Label *item = memnew(Label);
		item->set_text("Content item " + itos(i + 1));
		content->add_child(item);
	}
}

/*
 * Key Points:
 * 
 * 1. The scroll shadow only appears when scrolled down (v_scroll > 0)
 * 2. Shadow is drawn at the top of the ScrollContainer
 * 3. Compatible with all platforms and modern browsers
 * 4. Handles variable toolbar heights automatically
 * 5. Theme customization available for different visual styles
 * 6. Minimal performance impact - only redraws when scrolling with feature enabled
 * 7. Disabled by default - must be explicitly enabled
 */
