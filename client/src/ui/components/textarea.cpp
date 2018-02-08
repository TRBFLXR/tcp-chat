//
// Created by Igor on 2/6/2018.
//

#include "textarea.hpp"

ui::TextArea::TextArea(const std::wstring_view &name, const vec2u &pos, const vec2u &size, const HWND &parent, WORD id) :
		Component(pos, size, parent, id) {

	handle = CreateWindow(L"EDIT", name.data(),
	                      WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_READONLY |
	                      WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
	                      pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);

	setFont(L"Consolas");
}

void ui::TextArea::append(const std::wstring_view &text) const {
	DWORD StartPos, EndPos;
	SendMessage(handle, EM_GETSEL, reinterpret_cast<WPARAM>(&StartPos), reinterpret_cast<WPARAM>(&EndPos));

	int outLength = GetWindowTextLength(handle);
	SendMessage(handle, EM_SETSEL, static_cast<WPARAM>(outLength), outLength);

	SendMessage(handle, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(text.data()));

	SendMessage(handle, EM_SETSEL, StartPos, EndPos);
}
