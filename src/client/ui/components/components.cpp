//
// Created by Igor on 2/6/2018.
//

#include "components.hpp"
#include "../../../chatillo/test.hpp"

ui::Components::Components(const HWND &parent) :
		parent(parent),

		button1(L"button1", vec2u(20, 20), vec2u(100, 20), parent, 1),
		button2(L"button2", vec2u(20, 50), vec2u(100, 20), parent, 2),
		button3(L"button3", vec2u(20, 80), vec2u(100, 20), parent, 3),
		textArea(L"", vec2u(0, 120), vec2u(500, 320), parent, 0),
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
		case 3:
			textArea.append(textField.getText());
			textArea.append(std::to_wstring(Test::test()) + L"\n");
			break;
		default:
			break;
	}
}
