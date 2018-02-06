//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_TEXTAREA_HPP
#define TCP_CHAT_TEXTAREA_HPP


#include "component.hpp"

namespace ui {

	class TextArea : public Component {
	public:
		explicit TextArea(const std::wstring_view &text, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id);

		void append(const std::wstring_view &text) const;
	};

}


#endif //TCP_CHAT_TEXTAREA_HPP
