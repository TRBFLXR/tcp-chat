//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_BUTTON_HPP
#define TCP_CHAT_BUTTON_HPP


#include "component.hpp"
#include "../../util/style.hpp"

namespace ui {

	class Button : public Component {
	public:
		explicit Button(const std::wstring_view &caption, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id,
		                DWORD style = DEFAULT_BUTTON_STYLE);

	private:
		std::wstring caption;
	};

}

#endif //TCP_CHAT_BUTTON_HPP
