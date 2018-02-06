//
// Created by Igor on 2/6/2018.
//

#include "textfield.hpp"

ui::TextField::TextField(const std::wstring_view &text, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id)
		: Component(pos, size, parent, id) {

	handle = CreateWindow(L"EDIT", text.data(), WS_VISIBLE | WS_CHILD | WS_BORDER,
	                      pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);

	setFont(L"Consolas");
}

std::wstring ui::TextField::getText() const {
	int size = GetWindowTextLength(handle) + 1;
	WCHAR buffer[size];

	GetWindowText(handle, buffer, size);

	return std::wstring(buffer);
}
