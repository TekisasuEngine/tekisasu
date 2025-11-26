/**************************************************************************/
/*  scene_debugger.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                            TEKISASU ENGINE                             */
/*                       https://dev.tekisasu.com                         */
/**************************************************************************/
/* Copyright (c) 2021-present Tekisasu (see AUTHORS.md).                  */
/* Copyright (c) 2024-present Blazium (see BLAZIUM.md).                   */
/* Copyright (c) 2014-present Godot Engine contributors (see GODOT.md).   */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
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

#include "scene_debugger.h"

#include "core/debugger/engine_debugger.h"
#include "core/debugger/engine_profiler.h"
#include "core/io/marshalls.h"
#include "core/math/math_funcs.h"
#include "core/object/script_language.h"
#include "core/templates/local_vector.h"
#include "scene/main/scene_tree.h"
#include "scene/main/window.h"
#include "scene/resources/packed_scene.h"
#include "servers/audio/audio_effect.h"
#include "servers/audio_server.h"

SceneDebugger *SceneDebugger::singleton = nullptr;

SceneDebugger::SceneDebugger() {
	singleton = this;
#ifdef DEBUG_ENABLED
	LiveEditor::singleton = memnew(LiveEditor);
	EngineDebugger::register_message_capture("scene", EngineDebugger::Capture(nullptr, SceneDebugger::parse_message));
#endif
}

SceneDebugger::~SceneDebugger() {
#ifdef DEBUG_ENABLED
	if (LiveEditor::singleton) {
		EngineDebugger::unregister_message_capture("scene");
		memdelete(LiveEditor::singleton);
		LiveEditor::singleton = nullptr;
	}
#endif
	singleton = nullptr;
}

void SceneDebugger::initialize() {
	if (EngineDebugger::is_active()) {
		memnew(SceneDebugger);
	}
}

void SceneDebugger::deinitialize() {
	if (singleton) {
		memdelete(singleton);
	}
}

#ifdef DEBUG_ENABLED
Error SceneDebugger::parse_message(void *p_user, const String &p_msg, const Array &p_args, bool &r_captured) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return ERR_UNCONFIGURED;
	}
	LiveEditor *live_editor = LiveEditor::get_singleton();
	if (!live_editor) {
		return ERR_UNCONFIGURED;
	}

	r_captured = true;
	if (p_msg == "request_scene_tree") { // Scene tree
		live_editor->_send_tree();

	} else if (p_msg == "save_node") { // Save node.
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		_save_node(p_args[0], p_args[1]);
		Array arr;
		arr.append(p_args[1]);
		EngineDebugger::get_singleton()->send_message("filesystem:update_file", { arr });

	} else if (p_msg == "inspect_object") { // Object Inspect
		ERR_FAIL_COND_V(p_args.is_empty(), ERR_INVALID_DATA);
		ObjectID id = p_args[0];
		_send_object_id(id);

	} else if (p_msg == "override_camera_2D:set") { // Camera
		ERR_FAIL_COND_V(p_args.is_empty(), ERR_INVALID_DATA);
		bool enforce = p_args[0];
		scene_tree->get_root()->enable_canvas_transform_override(enforce);

	} else if (p_msg == "override_camera_2D:transform") {
		ERR_FAIL_COND_V(p_args.is_empty(), ERR_INVALID_DATA);
		Transform2D transform = p_args[0];
		scene_tree->get_root()->set_canvas_transform_override(transform);
#ifndef _3D_DISABLED
	} else if (p_msg == "override_camera_3D:set") {
		ERR_FAIL_COND_V(p_args.is_empty(), ERR_INVALID_DATA);
		bool enable = p_args[0];
		scene_tree->get_root()->enable_camera_3d_override(enable);

	} else if (p_msg == "override_camera_3D:transform") {
		ERR_FAIL_COND_V(p_args.size() < 5, ERR_INVALID_DATA);
		Transform3D transform = p_args[0];
		bool is_perspective = p_args[1];
		float size_or_fov = p_args[2];
		float depth_near = p_args[3];
		float depth_far = p_args[4];
		if (is_perspective) {
			scene_tree->get_root()->set_camera_3d_override_perspective(size_or_fov, depth_near, depth_far);
		} else {
			scene_tree->get_root()->set_camera_3d_override_orthogonal(size_or_fov, depth_near, depth_far);
		}
		scene_tree->get_root()->set_camera_3d_override_transform(transform);
#endif // _3D_DISABLED
	} else if (p_msg == "set_object_property") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		_set_object_property(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "sync_audio_buses") {
		ERR_FAIL_COND_V(p_args.size() < 1, ERR_INVALID_DATA);
		ERR_FAIL_COND_V(p_args[0].get_type() != Variant::DICTIONARY, ERR_INVALID_DATA);

		Dictionary layout = p_args[0];
		if (!layout.has("buses")) {
			return ERR_INVALID_DATA;
		}

		Array buses = layout["buses"];

		AudioServer *as = AudioServer::get_singleton();
		if (!as) {
			return ERR_UNAVAILABLE;
		}

		// Ensure we can safely apply while a scene is running.
		if (!SceneTree::get_singleton() || !SceneTree::get_singleton()->get_root()) {
			return ERR_UNAVAILABLE;
		}

		// Resize bus count to match.
		const int target_count = buses.size();
		int current_count = as->get_bus_count();
		// Add buses if needed.
		while (current_count < target_count) {
			as->add_bus(-1);
			current_count++;
		}
		// Remove extra buses (but never remove Master at index 0).
		while (current_count > target_count && current_count > 1) {
			as->remove_bus(current_count - 1);
			current_count--;
		}

		// Apply per-bus properties.
		const int apply_count = MIN(current_count, target_count);
		for (int i = 0; i < apply_count; i++) {
			Dictionary b = buses[i];
			if (b.has("name")) {
				const String want = String(b["name"]);
				if (as->get_bus_name(i) != want) {
					as->set_bus_name(i, want);
				}
			}
			if (b.has("send")) {
				const StringName want = StringName(String(b["send"]));
				if (as->get_bus_send(i) != want) {
					as->set_bus_send(i, want);
				}
			}
			if (b.has("volume_db")) {
				const float want = (float)b["volume_db"];
				if (!Math::is_equal_approx(as->get_bus_volume_db(i), want)) {
					as->set_bus_volume_db(i, want);
				}
			}
			if (b.has("solo")) {
				const bool want = (bool)b["solo"];
				if (as->is_bus_solo(i) != want) {
					as->set_bus_solo(i, want);
				}
			}
			if (b.has("mute")) {
				const bool want = (bool)b["mute"];
				if (as->is_bus_mute(i) != want) {
					as->set_bus_mute(i, want);
				}
			}
			if (b.has("bypass")) {
				const bool want = (bool)b["bypass"];
				if (as->is_bus_bypassing_effects(i) != want) {
					as->set_bus_bypass_effects(i, want);
				}
			}

			// Effects: update in place to minimize interruptions (minimal-diff using LCS).
			if (b.has("effects") && Variant(b["effects"]).get_type() == Variant::ARRAY) {
				Array effects = b["effects"];
				const int curr_count = as->get_bus_effect_count(i);
				const int incoming_count = effects.size();

				// Gather current and desired class sequences.
				Vector<String> curr;
				curr.resize(curr_count);
				for (int e = 0; e < curr_count; e++) {
					Ref<AudioEffect> ex = as->get_bus_effect(i, e);
					curr.write[e] = ex.is_valid() ? ex->get_class() : String();
				}
				Vector<String> want;
				want.resize(incoming_count);
				for (int e = 0; e < incoming_count; e++) {
					Dictionary fx = effects[e];
					want.write[e] = fx.has("class") ? String(fx["class"]) : String();
				}

				// Compute LCS of class names.
				const int n = curr.size();
				const int m = want.size();
				Vector<Vector<int>> dp;
				dp.resize(n + 1);
				for (int ii = 0; ii <= n; ii++) {
					dp.write[ii].resize(m + 1);
					for (int jj = 0; jj <= m; jj++) {
						dp.write[ii].write[jj] = 0;
					}
				}
				for (int ii = 1; ii <= n; ii++) {
					for (int jj = 1; jj <= m; jj++) {
						if (curr[ii - 1] == want[jj - 1]) {
							dp.write[ii].write[jj] = dp[ii - 1][jj - 1] + 1;
						} else {
							dp.write[ii].write[jj] = MAX(dp[ii - 1][jj], dp[ii][jj - 1]);
						}
					}
				}

				// Build LCS sequence (class names) without push_front by filling backwards.
				Vector<String> lcs;
				{
					const int lcs_len = dp[n][m];
					lcs.resize(lcs_len);
					int pos = lcs_len - 1;
					int ii = n, jj = m;
					while (ii > 0 && jj > 0) {
						if (curr[ii - 1] == want[jj - 1]) {
							if (pos >= 0) {
								lcs.write[pos] = curr[ii - 1];
								pos--;
							}
							ii--;
							jj--;
						} else if (dp[ii - 1][jj] >= dp[ii][jj - 1]) {
							ii--;
						} else {
							jj--;
						}
					}
				}

				// Transform current chain into desired using LCS-guided edits.
				int ci = 0, wi = 0, li = 0;
				while (li < lcs.size()) {
					// Remove non-LCS from current at position ci.
					while (ci < as->get_bus_effect_count(i)) {
						Ref<AudioEffect> ex = as->get_bus_effect(i, ci);
						String ex_class = ex.is_valid() ? ex->get_class() : String();
						if (ex_class == lcs[li]) {
							break;
						}
						as->remove_bus_effect(i, ci); // removal shifts next into this index
					}
					// Insert missing desired until we reach LCS token.
					while (wi < want.size() && want[wi] != lcs[li]) {
						const String class_name = want[wi];
						if (!class_name.is_empty()) {
							Ref<AudioEffect> afxr = Object::cast_to<AudioEffect>(ClassDB::instantiate(class_name));
							if (afxr.is_valid()) {
								as->add_bus_effect(i, afxr, ci);
								ci++; // advance past inserted
							}
						}
						wi++;
					}
					// Skip the LCS token in both sequences.
					if (ci < as->get_bus_effect_count(i)) {
						ci++;
					}
					if (wi < want.size()) {
						wi++;
					}
					li++;
				}
				// Remove any remaining extras from current.
				while (ci < as->get_bus_effect_count(i)) {
					as->remove_bus_effect(i, ci);
				}
				// Append any remaining desired.
				while (wi < want.size()) {
					const String class_name = want[wi];
					if (!class_name.is_empty()) {
						Ref<AudioEffect> afxr = Object::cast_to<AudioEffect>(ClassDB::instantiate(class_name));
						if (afxr.is_valid()) {
							as->add_bus_effect(i, afxr, -1);
						}
					}
					wi++;
				}

				// Apply parameters and enabled flags for all incoming effects.
				for (int e = 0; e < incoming_count; e++) {
					Dictionary fx = effects[e];
					const int final_count = as->get_bus_effect_count(i);
					Ref<AudioEffect> eff = (e < final_count) ? as->get_bus_effect(i, e) : Ref<AudioEffect>();
					if (eff.is_valid() && fx.has("params") && Variant(fx["params"]).get_type() == Variant::DICTIONARY) {
						Dictionary params = fx["params"];
						List<Variant> keys;
						params.get_key_list(&keys);
						for (const Variant &k : keys) {
							const StringName prop = StringName(String(k));
							const Variant &val = params[k];
							Variant cur = eff->get(prop);
							if (cur != val) {
								eff->set(prop, val);
							}
						}
					}
					if (fx.has("enabled") && e < final_count) {
						bool want_enabled = (bool)fx["enabled"];
						if (as->is_bus_effect_enabled(i, e) != want_enabled) {
							as->set_bus_effect_enabled(i, e, want_enabled);
						}
					}
				}
			}
		}

	} else if (!p_msg.begins_with("live_")) { // Live edits below.
		return ERR_SKIP;
	} else if (p_msg == "live_set_root") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		live_editor->_root_func(p_args[0], p_args[1]);

	} else if (p_msg == "live_node_path") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		live_editor->_node_path_func(p_args[0], p_args[1]);

	} else if (p_msg == "live_res_path") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		live_editor->_res_path_func(p_args[0], p_args[1]);

	} else if (p_msg == "live_node_prop_res") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_node_set_res_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_node_prop") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_node_set_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_res_prop_res") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_res_set_res_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_res_prop") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_res_set_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_node_call") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		LocalVector<Variant> args;
		LocalVector<Variant *> argptrs;
		args.resize(p_args.size() - 2);
		argptrs.resize(args.size());
		for (uint32_t i = 0; i < args.size(); i++) {
			args[i] = p_args[i + 2];
			argptrs[i] = &args[i];
		}
		live_editor->_node_call_func(p_args[0], p_args[1], argptrs.size() ? (const Variant **)argptrs.ptr() : nullptr, argptrs.size());

	} else if (p_msg == "live_res_call") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		LocalVector<Variant> args;
		LocalVector<Variant *> argptrs;
		args.resize(p_args.size() - 2);
		argptrs.resize(args.size());
		for (uint32_t i = 0; i < args.size(); i++) {
			args[i] = p_args[i + 2];
			argptrs[i] = &args[i];
		}
		live_editor->_res_call_func(p_args[0], p_args[1], argptrs.size() ? (const Variant **)argptrs.ptr() : nullptr, argptrs.size());

	} else if (p_msg == "live_create_node") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_create_node_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_instantiate_node") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_instance_node_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_remove_node") {
		ERR_FAIL_COND_V(p_args.is_empty(), ERR_INVALID_DATA);
		live_editor->_remove_node_func(p_args[0]);

	} else if (p_msg == "live_remove_and_keep_node") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		live_editor->_remove_and_keep_node_func(p_args[0], p_args[1]);

	} else if (p_msg == "live_restore_node") {
		ERR_FAIL_COND_V(p_args.size() < 3, ERR_INVALID_DATA);
		live_editor->_restore_node_func(p_args[0], p_args[1], p_args[2]);

	} else if (p_msg == "live_duplicate_node") {
		ERR_FAIL_COND_V(p_args.size() < 2, ERR_INVALID_DATA);
		live_editor->_duplicate_node_func(p_args[0], p_args[1]);

	} else if (p_msg == "live_reparent_node") {
		ERR_FAIL_COND_V(p_args.size() < 4, ERR_INVALID_DATA);
		live_editor->_reparent_node_func(p_args[0], p_args[1], p_args[2], p_args[3]);
	} else {
		r_captured = false;
	}
	return OK;
}

void SceneDebugger::_save_node(ObjectID id, const String &p_path) {
	Node *node = Object::cast_to<Node>(ObjectDB::get_instance(id));
	ERR_FAIL_NULL(node);

#ifdef TOOLS_ENABLED
	HashMap<const Node *, Node *> duplimap;
	Node *copy = node->duplicate_from_editor(duplimap);
#else
	Node *copy = node->duplicate();
#endif

	// Handle Unique Nodes.
	for (int i = 0; i < copy->get_child_count(false); i++) {
		_set_node_owner_recursive(copy->get_child(i, false), copy);
	}
	// Root node cannot ever be unique name in its own Scene!
	copy->set_unique_name_in_owner(false);

	Ref<PackedScene> ps = memnew(PackedScene);
	ps->pack(copy);
	ResourceSaver::save(ps, p_path);

	memdelete(copy);
}

void SceneDebugger::_set_node_owner_recursive(Node *p_node, Node *p_owner) {
	if (!p_node->get_owner()) {
		p_node->set_owner(p_owner);
	}

	for (int i = 0; i < p_node->get_child_count(false); i++) {
		_set_node_owner_recursive(p_node->get_child(i, false), p_owner);
	}
}

void SceneDebugger::_send_object_id(ObjectID p_id, int p_max_size) {
	SceneDebuggerObject obj(p_id);
	if (obj.id.is_null()) {
		return;
	}

	Array arr;
	obj.serialize(arr);
	EngineDebugger::get_singleton()->send_message("scene:inspect_object", arr);
}

void SceneDebugger::_set_object_property(ObjectID p_id, const String &p_property, const Variant &p_value) {
	Object *obj = ObjectDB::get_instance(p_id);
	if (!obj) {
		return;
	}

	String prop_name = p_property;
	if (p_property.begins_with("Members/")) {
		Vector<String> ss = p_property.split("/");
		prop_name = ss[ss.size() - 1];
	}

	obj->set(prop_name, p_value);
}

void SceneDebugger::add_to_cache(const String &p_filename, Node *p_node) {
	LiveEditor *debugger = LiveEditor::get_singleton();
	if (!debugger) {
		return;
	}

	if (EngineDebugger::get_script_debugger() && !p_filename.is_empty()) {
		debugger->live_scene_edit_cache[p_filename].insert(p_node);
	}
}

void SceneDebugger::remove_from_cache(const String &p_filename, Node *p_node) {
	LiveEditor *debugger = LiveEditor::get_singleton();
	if (!debugger) {
		return;
	}

	HashMap<String, HashSet<Node *>> &edit_cache = debugger->live_scene_edit_cache;
	HashMap<String, HashSet<Node *>>::Iterator E = edit_cache.find(p_filename);
	if (E) {
		E->value.erase(p_node);
		if (E->value.size() == 0) {
			edit_cache.remove(E);
		}
	}

	HashMap<Node *, HashMap<ObjectID, Node *>> &remove_list = debugger->live_edit_remove_list;
	HashMap<Node *, HashMap<ObjectID, Node *>>::Iterator F = remove_list.find(p_node);
	if (F) {
		for (const KeyValue<ObjectID, Node *> &G : F->value) {
			memdelete(G.value);
		}
		remove_list.remove(F);
	}
}

/// SceneDebuggerObject
SceneDebuggerObject::SceneDebuggerObject(ObjectID p_id) {
	id = ObjectID();
	Object *obj = ObjectDB::get_instance(p_id);
	if (!obj) {
		return;
	}

	id = p_id;
	class_name = obj->get_class();

	if (ScriptInstance *si = obj->get_script_instance()) {
		// Read script instance constants and variables
		if (!si->get_script().is_null()) {
			Script *s = si->get_script().ptr();
			_parse_script_properties(s, si);
		}
	}

	if (Node *node = Object::cast_to<Node>(obj)) {
		// For debugging multiplayer.
		{
			PropertyInfo pi(Variant::INT, String("Node/multiplayer_authority"), PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_READ_ONLY);
			properties.push_back(SceneDebuggerProperty(pi, node->get_multiplayer_authority()));
		}

		// Add specialized NodePath info (if inside tree).
		if (node->is_inside_tree()) {
			PropertyInfo pi(Variant::NODE_PATH, String("Node/path"));
			properties.push_back(SceneDebuggerProperty(pi, node->get_path()));
		} else { // Can't ask for path if a node is not in tree.
			PropertyInfo pi(Variant::STRING, String("Node/path"));
			properties.push_back(SceneDebuggerProperty(pi, "[Orphan]"));
		}
	} else if (Script *s = Object::cast_to<Script>(obj)) {
		// Add script constants (no instance).
		_parse_script_properties(s, nullptr);
	}

	// Add base object properties.
	List<PropertyInfo> pinfo;
	obj->get_property_list(&pinfo, true);
	for (const PropertyInfo &E : pinfo) {
		if (E.usage & (PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_CATEGORY)) {
			properties.push_back(SceneDebuggerProperty(E, obj->get(E.name)));
		}
	}
}

void SceneDebuggerObject::_parse_script_properties(Script *p_script, ScriptInstance *p_instance) {
	typedef HashMap<const Script *, HashSet<StringName>> ScriptMemberMap;
	typedef HashMap<const Script *, HashMap<StringName, Variant>> ScriptConstantsMap;

	ScriptMemberMap members;
	if (p_instance) {
		members[p_script] = HashSet<StringName>();
		p_script->get_members(&(members[p_script]));
	}

	ScriptConstantsMap constants;
	constants[p_script] = HashMap<StringName, Variant>();
	p_script->get_constants(&(constants[p_script]));

	Ref<Script> base = p_script->get_base_script();
	while (base.is_valid()) {
		if (p_instance) {
			members[base.ptr()] = HashSet<StringName>();
			base->get_members(&(members[base.ptr()]));
		}

		constants[base.ptr()] = HashMap<StringName, Variant>();
		base->get_constants(&(constants[base.ptr()]));

		base = base->get_base_script();
	}

	// Members
	for (KeyValue<const Script *, HashSet<StringName>> sm : members) {
		for (const StringName &E : sm.value) {
			Variant m;
			if (p_instance->get(E, m)) {
				String script_path = sm.key == p_script ? "" : sm.key->get_path().get_file() + "/";
				PropertyInfo pi(m.get_type(), "Members/" + script_path + E);
				properties.push_back(SceneDebuggerProperty(pi, m));
			}
		}
	}
	// Constants
	for (KeyValue<const Script *, HashMap<StringName, Variant>> &sc : constants) {
		for (const KeyValue<StringName, Variant> &E : sc.value) {
			String script_path = sc.key == p_script ? "" : sc.key->get_path().get_file() + "/";
			if (E.value.get_type() == Variant::OBJECT) {
				Variant inst_id = ((Object *)E.value)->get_instance_id();
				PropertyInfo pi(inst_id.get_type(), "Constants/" + E.key, PROPERTY_HINT_OBJECT_ID, "Object");
				properties.push_back(SceneDebuggerProperty(pi, inst_id));
			} else {
				PropertyInfo pi(E.value.get_type(), "Constants/" + script_path + E.key);
				properties.push_back(SceneDebuggerProperty(pi, E.value));
			}
		}
	}
}

void SceneDebuggerObject::serialize(Array &r_arr, int p_max_size) {
	Array send_props;
	for (SceneDebuggerObject::SceneDebuggerProperty &property : properties) {
		const PropertyInfo &pi = property.first;
		Variant &var = property.second;

		Ref<Resource> res = var;

		Array prop;
		prop.push_back(pi.name);
		prop.push_back(pi.type);

		PropertyHint hint = pi.hint;
		String hint_string = pi.hint_string;
		if (!res.is_null() && !res->get_path().is_empty()) {
			var = res->get_path();
		} else { //only send information that can be sent..
			int len = 0; //test how big is this to encode
			encode_variant(var, nullptr, len);
			if (len > p_max_size) { //limit to max size
				hint = PROPERTY_HINT_OBJECT_TOO_BIG;
				hint_string = "";
				var = Variant();
			}
		}
		prop.push_back(hint);
		prop.push_back(hint_string);
		prop.push_back(pi.usage);
		prop.push_back(var);
		send_props.push_back(prop);
	}
	r_arr.push_back(uint64_t(id));
	r_arr.push_back(class_name);
	r_arr.push_back(send_props);
}

void SceneDebuggerObject::deserialize(const Array &p_arr) {
#define CHECK_TYPE(p_what, p_type) ERR_FAIL_COND(p_what.get_type() != Variant::p_type);
	ERR_FAIL_COND(p_arr.size() < 3);
	CHECK_TYPE(p_arr[0], INT);
	CHECK_TYPE(p_arr[1], STRING);
	CHECK_TYPE(p_arr[2], ARRAY);

	id = uint64_t(p_arr[0]);
	class_name = p_arr[1];
	Array props = p_arr[2];

	for (int i = 0; i < props.size(); i++) {
		CHECK_TYPE(props[i], ARRAY);
		Array prop = props[i];

		ERR_FAIL_COND(prop.size() != 6);
		CHECK_TYPE(prop[0], STRING);
		CHECK_TYPE(prop[1], INT);
		CHECK_TYPE(prop[2], INT);
		CHECK_TYPE(prop[3], STRING);
		CHECK_TYPE(prop[4], INT);

		PropertyInfo pinfo;
		pinfo.name = prop[0];
		pinfo.type = Variant::Type(int(prop[1]));
		pinfo.hint = PropertyHint(int(prop[2]));
		pinfo.hint_string = prop[3];
		pinfo.usage = PropertyUsageFlags(int(prop[4]));
		Variant var = prop[5];

		if (pinfo.type == Variant::OBJECT) {
			if (var.is_zero()) {
				var = Ref<Resource>();
			} else if (var.get_type() == Variant::OBJECT) {
				if (((Object *)var)->is_class("EncodedObjectAsID")) {
					var = Object::cast_to<EncodedObjectAsID>(var)->get_object_id();
					pinfo.type = var.get_type();
					pinfo.hint = PROPERTY_HINT_OBJECT_ID;
					pinfo.hint_string = "Object";
				}
			}
		}
		properties.push_back(SceneDebuggerProperty(pinfo, var));
	}
}

/// SceneDebuggerTree
SceneDebuggerTree::SceneDebuggerTree(Node *p_root) {
	// Flatten tree into list, depth first, use stack to avoid recursion.
	List<Node *> stack;
	stack.push_back(p_root);
	bool is_root = true;
	const StringName &is_visible_sn = SNAME("is_visible");
	const StringName &is_visible_in_tree_sn = SNAME("is_visible_in_tree");
	while (stack.size()) {
		Node *n = stack.front()->get();
		stack.pop_front();

		int count = n->get_child_count();
		for (int i = 0; i < count; i++) {
			stack.push_front(n->get_child(count - i - 1));
		}

		int view_flags = 0;
		if (is_root) {
			// Prevent root window visibility from being changed.
			is_root = false;
		} else if (n->has_method(is_visible_sn)) {
			const Variant visible = n->call(is_visible_sn);
			if (visible.get_type() == Variant::BOOL) {
				view_flags = RemoteNode::VIEW_HAS_VISIBLE_METHOD;
				view_flags |= uint8_t(visible) * RemoteNode::VIEW_VISIBLE;
			}
			if (n->has_method(is_visible_in_tree_sn)) {
				const Variant visible_in_tree = n->call(is_visible_in_tree_sn);
				if (visible_in_tree.get_type() == Variant::BOOL) {
					view_flags |= uint8_t(visible_in_tree) * RemoteNode::VIEW_VISIBLE_IN_TREE;
				}
			}
		}
		nodes.push_back(RemoteNode(count, n->get_name(), n->get_class(), n->get_instance_id(), n->get_scene_file_path(), view_flags));
	}
}

void SceneDebuggerTree::serialize(Array &p_arr) {
	for (const RemoteNode &n : nodes) {
		p_arr.push_back(n.child_count);
		p_arr.push_back(n.name);
		p_arr.push_back(n.type_name);
		p_arr.push_back(n.id);
		p_arr.push_back(n.scene_file_path);
		p_arr.push_back(n.view_flags);
	}
}

void SceneDebuggerTree::deserialize(const Array &p_arr) {
	int idx = 0;
	while (p_arr.size() > idx) {
		ERR_FAIL_COND(p_arr.size() < 6);
		CHECK_TYPE(p_arr[idx], INT); // child_count.
		CHECK_TYPE(p_arr[idx + 1], STRING); // name.
		CHECK_TYPE(p_arr[idx + 2], STRING); // type_name.
		CHECK_TYPE(p_arr[idx + 3], INT); // id.
		CHECK_TYPE(p_arr[idx + 4], STRING); // scene_file_path.
		CHECK_TYPE(p_arr[idx + 5], INT); // view_flags.
		nodes.push_back(RemoteNode(p_arr[idx], p_arr[idx + 1], p_arr[idx + 2], p_arr[idx + 3], p_arr[idx + 4], p_arr[idx + 5]));
		idx += 6;
	}
}

/// LiveEditor
LiveEditor *LiveEditor::singleton = nullptr;
LiveEditor *LiveEditor::get_singleton() {
	return singleton;
}

void LiveEditor::_send_tree() {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Array arr;
	// Encoded as a flat list depth first.
	SceneDebuggerTree tree(scene_tree->root);
	tree.serialize(arr);
	EngineDebugger::get_singleton()->send_message("scene:scene_tree", arr);
}

void LiveEditor::_node_path_func(const NodePath &p_path, int p_id) {
	live_edit_node_path_cache[p_id] = p_path;
}

void LiveEditor::_res_path_func(const String &p_path, int p_id) {
	live_edit_resource_cache[p_id] = p_path;
}

void LiveEditor::_node_set_func(int p_id, const StringName &p_prop, const Variant &p_value) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	if (!live_edit_node_path_cache.has(p_id)) {
		return;
	}

	NodePath np = live_edit_node_path_cache[p_id];
	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(np)) {
			continue;
		}
		Node *n2 = n->get_node(np);

		// Do not change transform of edited scene root, unless it's the scene being played.
		// See GH-86659 for additional context.
		bool keep_transform = (n2 == n) && (n2->get_parent() != scene_tree->root);
		Variant orig_tf;

		if (keep_transform) {
			if (n2->is_class("Node3D")) {
				orig_tf = n2->call("get_transform");
			} else if (n2->is_class("CanvasItem")) {
				orig_tf = n2->call("_edit_get_state");
			}
		}

		n2->set(p_prop, p_value);

		if (keep_transform) {
			if (n2->is_class("Node3D")) {
				Variant new_tf = n2->call("get_transform");
				if (new_tf != orig_tf) {
					n2->call("set_transform", orig_tf);
				}
			} else if (n2->is_class("CanvasItem")) {
				Variant new_tf = n2->call("_edit_get_state");
				if (new_tf != orig_tf) {
					n2->call("_edit_set_state", orig_tf);
				}
			}
		}
	}
}

void LiveEditor::_node_set_res_func(int p_id, const StringName &p_prop, const String &p_value) {
	Ref<Resource> r = ResourceLoader::load(p_value);
	if (!r.is_valid()) {
		return;
	}
	_node_set_func(p_id, p_prop, r);
}

void LiveEditor::_node_call_func(int p_id, const StringName &p_method, const Variant **p_args, int p_argcount) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}
	if (!live_edit_node_path_cache.has(p_id)) {
		return;
	}

	NodePath np = live_edit_node_path_cache[p_id];
	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(np)) {
			continue;
		}
		Node *n2 = n->get_node(np);

		// Do not change transform of edited scene root, unless it's the scene being played.
		// See GH-86659 for additional context.
		bool keep_transform = (n2 == n) && (n2->get_parent() != scene_tree->root);
		Variant orig_tf;

		if (keep_transform) {
			if (n2->is_class("Node3D")) {
				orig_tf = n2->call("get_transform");
			} else if (n2->is_class("CanvasItem")) {
				orig_tf = n2->call("_edit_get_state");
			}
		}

		Callable::CallError ce;
		n2->callp(p_method, p_args, p_argcount, ce);

		if (keep_transform) {
			if (n2->is_class("Node3D")) {
				Variant new_tf = n2->call("get_transform");
				if (new_tf != orig_tf) {
					n2->call("set_transform", orig_tf);
				}
			} else if (n2->is_class("CanvasItem")) {
				Variant new_tf = n2->call("_edit_get_state");
				if (new_tf != orig_tf) {
					n2->call("_edit_set_state", orig_tf);
				}
			}
		}
	}
}

void LiveEditor::_res_set_func(int p_id, const StringName &p_prop, const Variant &p_value) {
	if (!live_edit_resource_cache.has(p_id)) {
		return;
	}

	String resp = live_edit_resource_cache[p_id];

	if (!ResourceCache::has(resp)) {
		return;
	}

	Ref<Resource> r = ResourceCache::get_ref(resp);
	if (!r.is_valid()) {
		return;
	}

	r->set(p_prop, p_value);
}

void LiveEditor::_res_set_res_func(int p_id, const StringName &p_prop, const String &p_value) {
	Ref<Resource> r = ResourceLoader::load(p_value);
	if (!r.is_valid()) {
		return;
	}
	_res_set_func(p_id, p_prop, r);
}

void LiveEditor::_res_call_func(int p_id, const StringName &p_method, const Variant **p_args, int p_argcount) {
	if (!live_edit_resource_cache.has(p_id)) {
		return;
	}

	String resp = live_edit_resource_cache[p_id];

	if (!ResourceCache::has(resp)) {
		return;
	}

	Ref<Resource> r = ResourceCache::get_ref(resp);
	if (!r.is_valid()) {
		return;
	}

	Callable::CallError ce;
	r->callp(p_method, p_args, p_argcount, ce);
}

void LiveEditor::_root_func(const NodePath &p_scene_path, const String &p_scene_from) {
	live_edit_root = p_scene_path;
	live_edit_scene = p_scene_from;
}

void LiveEditor::_create_node_func(const NodePath &p_parent, const String &p_type, const String &p_name) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_parent)) {
			continue;
		}
		Node *n2 = n->get_node(p_parent);

		Node *no = Object::cast_to<Node>(ClassDB::instantiate(p_type));
		if (!no) {
			continue;
		}

		no->set_name(p_name);
		n2->add_child(no);
	}
}

void LiveEditor::_instance_node_func(const NodePath &p_parent, const String &p_path, const String &p_name) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Ref<PackedScene> ps = ResourceLoader::load(p_path);

	if (!ps.is_valid()) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_parent)) {
			continue;
		}
		Node *n2 = n->get_node(p_parent);

		Node *no = ps->instantiate();
		if (!no) {
			continue;
		}

		no->set_name(p_name);
		n2->add_child(no);
	}
}

void LiveEditor::_remove_node_func(const NodePath &p_at) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	Vector<Node *> to_delete;

	for (HashSet<Node *>::Iterator F = E->value.begin(); F; ++F) {
		Node *n = *F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_at)) {
			continue;
		}
		Node *n2 = n->get_node(p_at);

		to_delete.push_back(n2);
	}

	for (int i = 0; i < to_delete.size(); i++) {
		memdelete(to_delete[i]);
	}
}

void LiveEditor::_remove_and_keep_node_func(const NodePath &p_at, ObjectID p_keep_id) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	Vector<Node *> to_remove;
	for (HashSet<Node *>::Iterator F = E->value.begin(); F; ++F) {
		Node *n = *F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_at)) {
			continue;
		}

		to_remove.push_back(n);
	}

	for (int i = 0; i < to_remove.size(); i++) {
		Node *n = to_remove[i];
		Node *n2 = n->get_node(p_at);
		n2->get_parent()->remove_child(n2);
		live_edit_remove_list[n][p_keep_id] = n2;
	}
}

void LiveEditor::_restore_node_func(ObjectID p_id, const NodePath &p_at, int p_at_pos) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (HashSet<Node *>::Iterator F = E->value.begin(); F;) {
		HashSet<Node *>::Iterator N = F;
		++N;

		Node *n = *F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_at)) {
			continue;
		}
		Node *n2 = n->get_node(p_at);

		HashMap<Node *, HashMap<ObjectID, Node *>>::Iterator EN = live_edit_remove_list.find(n);

		if (!EN) {
			continue;
		}

		HashMap<ObjectID, Node *>::Iterator FN = EN->value.find(p_id);

		if (!FN) {
			continue;
		}
		n2->add_child(FN->value);

		EN->value.remove(FN);

		if (EN->value.size() == 0) {
			live_edit_remove_list.remove(EN);
		}

		F = N;
	}
}

void LiveEditor::_duplicate_node_func(const NodePath &p_at, const String &p_new_name) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_at)) {
			continue;
		}
		Node *n2 = n->get_node(p_at);

		Node *dup = n2->duplicate(Node::DUPLICATE_SIGNALS | Node::DUPLICATE_GROUPS | Node::DUPLICATE_SCRIPTS);

		if (!dup) {
			continue;
		}

		dup->set_name(p_new_name);
		n2->get_parent()->add_child(dup);
	}
}

void LiveEditor::_reparent_node_func(const NodePath &p_at, const NodePath &p_new_place, const String &p_new_name, int p_at_pos) {
	SceneTree *scene_tree = SceneTree::get_singleton();
	if (!scene_tree) {
		return;
	}

	Node *base = nullptr;
	if (scene_tree->root->has_node(live_edit_root)) {
		base = scene_tree->root->get_node(live_edit_root);
	}

	HashMap<String, HashSet<Node *>>::Iterator E = live_scene_edit_cache.find(live_edit_scene);
	if (!E) {
		return; //scene not editable
	}

	for (Node *F : E->value) {
		Node *n = F;

		if (base && !base->is_ancestor_of(n)) {
			continue;
		}

		if (!n->has_node(p_at)) {
			continue;
		}
		Node *nfrom = n->get_node(p_at);

		if (!n->has_node(p_new_place)) {
			continue;
		}
		Node *nto = n->get_node(p_new_place);

		nfrom->get_parent()->remove_child(nfrom);
		nfrom->set_name(p_new_name);

		nto->add_child(nfrom);
		if (p_at_pos >= 0) {
			nto->move_child(nfrom, p_at_pos);
		}
	}
}

void SceneDebugger::_send_audio_peaks() {
	// Throttle to ~10 Hz using a frame counter (avoids OS tick queries).
	static int frame_counter = 0;
	static int stride = 6;
	// Adjust stride based on current FPS (~10 Hz target).
	const double fps = MAX(1.0, Engine::get_singleton()->get_frames_per_second());
	const int new_stride = CLAMP(int(Math::round(fps / 10.0)), 1, 30);
	if (new_stride != stride) {
		stride = new_stride;
		frame_counter = 0; // resync
	}
	if ((++frame_counter % stride) != 0) {
		return;
	}

	if (!EngineDebugger::is_active()) {
		return;
	}
	// Skip while scene is paused to avoid stale peak snapshots.
	SceneTree *st = SceneTree::get_singleton();
	if (st && st->is_paused()) {
		return;
	}

	AudioServer *as = AudioServer::get_singleton();
	if (!as) {
		return;
	}

	Array payload;
	const int bus_count = as->get_bus_count();
	for (int i = 0; i < bus_count; i++) {
		const int cc = as->get_bus_channels(i);
		PackedFloat32Array lefts;
		PackedFloat32Array rights;
		PackedByteArray actives;
		lefts.resize(cc);
		rights.resize(cc);
		actives.resize(cc);
		for (int c = 0; c < cc; c++) {
			lefts.write[c] = as->get_bus_peak_volume_left_db(i, c);
			rights.write[c] = as->get_bus_peak_volume_right_db(i, c);
			actives.write[c] = as->is_bus_channel_active(i, c) ? uint8_t(1) : uint8_t(0);
		}
		Array bus_arr;
		bus_arr.push_back(i);
		bus_arr.push_back(lefts);
		bus_arr.push_back(rights);
		bus_arr.push_back(actives);
		payload.push_back(bus_arr);
	}

	EngineDebugger::get_singleton()->send_message("scene:audio_peaks", payload);
}

void SceneDebugger::send_audio_peaks() {
	_send_audio_peaks();
}

#endif
