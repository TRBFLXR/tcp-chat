//
// Created by Igor on 2/6/2018.
//

#include "components.hpp"

ui::Components::Components(const HWND &parent) :
		parent(parent),

		button1(L"button1", {20, 20}, {100, 20}, parent, 1),
		button2(L"button2", {20, 50}, {100, 20}, parent, 2),
		button3(L"button3", {20, 80}, {100, 20}, parent, 3),
		textArea(L"", {0, 120}, {500, 320}, parent, 0),
		textField(L"", {130, 20}, {100, 20}, parent, 0) { }

void ui::Components::input(WORD id) {
	switch (id) {
		case 1:
			textField.setText(L"Test text");
			break;
		case 2:
			MessageBeep(MB_ICONERROR);
			MessageBox(parent, textField.getText().c_str(), L"Text", MB_OK);
			break;
		case 3:
			textArea.append(textField.getText() + L"\n");
			break;
		default:
			break;
	}
}
