//
// Created by Igor on 2/6/2018.
//

#include "textarea.hpp"
#include "../../config.hpp"

ui::TextArea::TextArea(const vec2u &pos, const vec2u &size, const HWND &parent, WORD id, DWORD style) :
		Component(pos, size, parent, id) {

	handle = CreateWindow(L"EDIT", L"", style,
	                      pos.x, pos.y, size.x, size.y, parent, reinterpret_cast<HMENU>(id), nullptr, nullptr);

	setFont(L"Consolas");
}

void ui::TextArea::append(const std::wstring_view &text) const {
	DWORD startPos;
	DWORD endPos;

	std::wstring formattedText;
	std::wstring buffer;
	size_t pbs = 0;

	if (text.size() > Config::lineWidth) {
		for (size_t i = 0; i < text.size(); ++i) {
			if (text[i] == L' ' || i == text.size() - 1) {
				if (buffer.size() > Config::lineWidth) {
					formattedText.append(buffer, 0, pbs);
					formattedText.append(L"\r\n   ");

					buffer.erase(0, pbs + 1);

					buffer += text[i];
					pbs = buffer.size() + Config::tabSize;
					continue;
				}
				pbs = buffer.size();
			}
			buffer += text[i];

			if (buffer.size() == Config::lineWidth - Config::tabSize) {
				formattedText.append(buffer);
				formattedText.append(L"\r\n   ");

				buffer.clear();
			}
		}
		formattedText.append(buffer);
	} else {
		formattedText = text.data();
	}

	SendMessage(handle, EM_GETSEL, reinterpret_cast<WPARAM>(&startPos), reinterpret_cast<WPARAM>(&endPos));

	int outLength = GetWindowTextLength(handle);
	SendMessage(handle, EM_SETSEL, static_cast<WPARAM>(outLength), outLength);

	SendMessage(handle, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(formattedText.c_str()));

	SendMessage(handle, EM_SETSEL, startPos, endPos);
}