//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_COMPONENT_HPP
#define TCP_CHAT_COMPONENT_HPP

#include <windows.h>
#include <string>

#include "../../util/types.hpp"

namespace ui {

	class Component {
	public:
		explicit Component(const vec2u &position, const vec2u &size, const HWND &parent, WORD id)
				: handle(nullptr), parent(parent), id(id), position(position), size(size) { };

		void setFont(const std::wstring_view &fontName, int size = 0) const {
			HFONT hfDefault = CreateFont(-size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontName.data());
			SendMessage(handle, WM_SETFONT, (WPARAM) hfDefault, MAKELPARAM(FALSE, 0));
		}

		void setFont(const HFONT &font) const {
			SendMessage(handle, WM_SETFONT, (WPARAM) font, MAKELPARAM(FALSE, 0));
		}

	protected:
		HWND handle;
		HWND parent;
		WORD id;

		vec2u position;
		vec2u size;
	};

}


#endif //TCP_CHAT_COMPONENT_HPP
