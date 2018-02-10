//
// Created by Igor on 2/10/2018.
//

#ifndef TCP_CHAT_LABEL_HPP
#define TCP_CHAT_LABEL_HPP


#include "component.hpp"

namespace ui {

	class Label : public Component {
	public:
		explicit Label(const std::wstring_view &text, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id);

	private:
		std::wstring text;
	};

}


#endif //TCP_CHAT_LABEL_HPP
