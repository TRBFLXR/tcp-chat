//
// Created by Igor on 2/9/2018.
//

#include <cassert>
#include "components.hpp"

ui::Components::Components(Application *app) : app(app) { }


void ui::Components::add(const std::string_view &name, ui::Component *component) {
	components.emplace(name, component);
}

ui::Component &ui::Components::get(const std::string_view &name) {
	auto c = components.find(name.data());
	assert(c != components.end() && "Could not find component");

	return *c->second;
}
