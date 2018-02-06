//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_COMPONENT_HPP
#define TCP_CHAT_COMPONENT_HPP

#include <windows.h>

#include "../../util/event.hpp"
#include "../../util/types.hpp"

namespace ui {

	class Component {
	public:
		explicit Component(const vec2u &position, const vec2u &size, const HWND &parent, WORD id)
				: parent(parent), id(id), position(position), size(size) { };

		virtual void handleEvent(Event &event) = 0;

	protected:
		HWND parent;
		WORD id;

		vec2u position;
		vec2u size;
	};

}


#endif //TCP_CHAT_COMPONENT_HPP
