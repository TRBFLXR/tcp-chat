//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_TEXTFIELD_HPP
#define TCP_CHAT_TEXTFIELD_HPP


#include <string>
#include "component.hpp"

namespace ui {

	class TextField : public Component {
	public:
		explicit TextField(const std::wstring_view &text, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id);

		inline int setText(const std::wstring_view &text) const { SetWindowText(handle, text.data()); }
		std::wstring getText() const;
	};

}


#endif //TCP_CHAT_TEXTFIELD_HPP
