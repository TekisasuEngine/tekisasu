extends Control
# Example script demonstrating the ScrollContainer scroll shadow feature
# This creates a simple UI with a scrollable list that shows the shadow effect

func _ready():
	# Create the main UI
	_setup_ui()

func _setup_ui():
	# Create a VBoxContainer to organize the demo
	var vbox = VBoxContainer.new()
	vbox.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(vbox)
	
	# Add a title
	var title = Label.new()
	title.text = "Scroll Shadow Demo"
	title.add_theme_font_size_override("font_size", 24)
	vbox.add_child(title)
	
	# Add instructions
	var instructions = Label.new()
	instructions.text = "Scroll down to see the shadow effect appear at the top"
	instructions.add_theme_font_size_override("font_size", 14)
	vbox.add_child(instructions)
	
	# Add toggle button
	var toggle = CheckButton.new()
	toggle.text = "Enable Scroll Shadow"
	toggle.button_pressed = true
	vbox.add_child(toggle)
	
	# Create a ScrollContainer with shadow enabled
	var scroll_container = ScrollContainer.new()
	scroll_container.scroll_shadow_enabled = true
	scroll_container.custom_minimum_size = Vector2(400, 300)
	vbox.add_child(scroll_container)
	
	# Connect the toggle button
	toggle.toggled.connect(func(enabled): scroll_container.scroll_shadow_enabled = enabled)
	
	# Create content for the scroll container
	var content = VBoxContainer.new()
	scroll_container.add_child(content)
	
	# Add many items to make it scrollable
	for i in range(50):
		var item = Button.new()
		item.text = "Item " + str(i + 1)
		item.custom_minimum_size = Vector2(0, 40)
		content.add_child(item)
	
	# Add a status label at the bottom
	var status = Label.new()
	status.text = "Scroll position: 0"
	vbox.add_child(status)
	
	# Update status label on scroll
	var vscroll = scroll_container.get_v_scroll_bar()
	vscroll.value_changed.connect(func(value): 
		status.text = "Scroll position: " + str(int(value))
		if value > 0:
			status.text += " (Shadow visible)"
		else:
			status.text += " (Shadow hidden)"
	)
