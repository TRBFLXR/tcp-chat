//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_COMPONENTS_HPP
#define TCP_CHAT_COMPONENTS_HPP


#include <minwindef.h>
#include <memory>
#include <unordered_map>
#include "components/component.hpp"

class Application;

namespace ui {

	class Window;

	class Components {
	public:
		explicit Components(Application *app, Window *parent);

		void add(const std::string_view &name, Component *component);
		Component &get(const std::string_view &name);

		virtual void input(WORD id) = 0;

		virtual void onCreate() { }

	protected:
		std::unordered_map<std::string, std::unique_ptr<Component>> components;

		Application *app;
		Window *parent;
	};

}


#endif //TCP_CHAT_COMPONENTS_HPP
