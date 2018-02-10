//
// Created by Igor on 2/10/2018.
//

#include "label.hpp"

ui::Label::Label(const std::wstring_view &text, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id) :
		Component(pos, size, parent, id),
		text(text) {

	handle = CreateWindow(L"STATIC", text.data(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_SIMPLE,
	                      pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);

	setFont(L"SansSerif", 14);
}
