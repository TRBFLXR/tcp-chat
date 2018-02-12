//
// Created by Igor on 2/12/2018.
//

#include "listbox.hpp"

ui::ListBox::ListBox(const vec2u &pos, const vec2u &size, const HWND &parent, WORD id, DWORD style) :
		Component(pos, size, parent, id) {

	handle = CreateWindow(L"LISTBOX", L"", style, pos.x, pos.y, size.x, size.y, parent,
	                      reinterpret_cast<HMENU>(id), nullptr, nullptr);

	setFont(L"Consolas");
}

void ui::ListBox::clear() const {
	SendMessage(handle, LB_RESETCONTENT, 0, 0);
}

void ui::ListBox::removeItem(const std::wstring_view &item) const {
	LRESULT count = SendMessage(handle, LB_GETCOUNT, 0, 0);
	if (count == LB_ERR) {
		MessageBox(parent, L"Cant remove item...", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	std::wstring buffer;
	for (int i = 0; i < count; ++i) {
		SendMessage(handle, LB_GETTEXT, static_cast<WPARAM>(i), reinterpret_cast<LPARAM>(buffer.data()));
		if (buffer.compare(item)) {
			SendMessage(handle, LB_DELETESTRING, static_cast<WPARAM>(i), 0);
			return;
		}
	}
}
