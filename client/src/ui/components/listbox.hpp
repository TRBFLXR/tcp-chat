//
// Created by Igor on 2/12/2018.
//

#ifndef TCP_CHAT_LISTBOX_HPP
#define TCP_CHAT_LISTBOX_HPP


#include "component.hpp"
#include "../../util/style.hpp"

namespace ui {

	class ListBox : public Component {
	public:
		explicit ListBox(const vec2u &pos, const vec2u &size, const HWND &parent, WORD id, DWORD style = DEFAULT_LISTBOX_STYLE);

		void clear() const;
		inline void addItem(const std::wstring_view &item) const { SendMessage(handle, LB_ADDSTRING, 0, (LPARAM) item.data()); }
		void removeItem(const std::wstring_view &item) const;
	};

}


#endif //TCP_CHAT_LISTBOX_HPP
