//
// Created by Igor on 2/6/2018.
//

#include "components.hpp"

ui::Components::Components(const HWND &parent) :
		parent(parent),

		button1(L"button1", vec2u(20, 20), vec2u(100, 20), parent, 1),
		button2(L"button2", vec2u(20, 50), vec2u(100, 20), parent, 2),
		textField(L"", vec2u(130, 20), vec2u(100, 20), parent, 0) { }

void ui::Components::input(WORD id) {
	switch (id) {
		case 1:
			textField.setText(L"Test text");
			break;
		case 2:
			MessageBeep(MB_ICONERROR);
			MessageBox(parent, textField.getText().c_str(), L"Text", MB_OK);
			break;
		default:
			break;
	}
}
