//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_TEXTFIELD_HPP
#define TCP_CHAT_TEXTFIELD_HPP


#include "component.hpp"
#include "../../util/style.hpp"

namespace ui {

	class TextField : public Component {
	public:
		explicit TextField(const vec2u &pos, const vec2u &size, const HWND &parent, WORD id, DWORD style = DEFAULT_EDIT_STYLE);

		inline int setText(const std::wstring_view &text) const { SetWindowText(handle, text.data()); }
		std::wstring getText() const;
	};

}


#endif //TCP_CHAT_TEXTFIELD_HPP
