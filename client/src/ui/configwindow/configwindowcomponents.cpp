//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "configwindowcomponents.hpp"
#include "../components/button.hpp"
#include "../components/textfield.hpp"

ui::ConfigWindowComponents::ConfigWindowComponents(Application* app, HWND parent) : Components(app, parent) {
	add("closeButton", new Button(L"Close", {20, 20}, {100, 20}, parent, 1));
	add("saveButton", new Button(L"Save", {20, 50}, {100, 20}, parent, 2));
	add("textFieldName", new TextField(L"", {130, 20}, {100, 20}, parent, 0));
	add("textFieldIP", new TextField(L"", {160, 50}, {100, 20}, parent, 0));
	add("textFieldPort", new TextField(L"", {190, 100}, {100, 20}, parent, 0));
}

void ui::ConfigWindowComponents::input(WORD id) {
	switch (id) {
		case 1:
			break;

		case 2:
			break;

		default:
			break;
	}
}
