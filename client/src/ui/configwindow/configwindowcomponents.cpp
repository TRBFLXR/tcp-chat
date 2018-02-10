//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "configwindowcomponents.hpp"
#include "../components/button.hpp"
#include "../components/textfield.hpp"
#include "../components/label.hpp"

ui::ConfigWindowComponents::ConfigWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("saveButton", new Button(L"Save", {20, 190}, {120, 20}, pHwnd, 1));
	add("closeButton", new Button(L"Close", {20, 220}, {120, 20}, pHwnd, 2));

	add("ipLabel", new Label(L"IP", {20, 10}, {120, 20}, pHwnd, 3));
	add("ipLabel", new Label(L"Port", {20, 65}, {120, 20}, pHwnd, 4));
	add("ipLabel", new Label(L"Name", {20, 120}, {120, 20}, pHwnd, 5));

	add("textFieldIP", new TextField({20, 30}, {120, 20}, pHwnd, 0));
	add("textFieldPort", new TextField({20, 85}, {120, 20}, pHwnd, 0));
	add("textFieldName", new TextField({20, 140}, {120, 20}, pHwnd, 0));
}

void ui::ConfigWindowComponents::input(WORD id) {
	switch (id) {
		case 1:
			((ConfigWindow *) parent)->shouldExit = false;
			break;

		case 2:
			break;

		case 0:
			break;
		default:
			break;
	}
}

void ui::ConfigWindowComponents::onCreate() {
	((TextField &) get("textFieldIP")).setText(L"255.255.255.255");
}
