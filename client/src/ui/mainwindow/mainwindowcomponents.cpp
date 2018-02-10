//
// Created by Igor on 2/9/2018.
//

#include <sstream>
#include "../../application.hpp"
#include "mainwindowcomponents.hpp"

ui::MainWindowComponents::MainWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("button1", new Button(L"set text", {20, 20}, {100, 20}, pHwnd, 1));
	add("button2", new Button(L"send", {20, 50}, {100, 20}, pHwnd, 2));
	add("button3", new Button(L"connect", {20, 80}, {100, 20}, pHwnd, 3));
	add("textArea1", new TextArea({0, 120}, {500, 320}, pHwnd, 0));
	add("textField1", new TextField({130, 20}, {100, 20}, pHwnd, 0));
}

void ui::MainWindowComponents::input(WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case 1:
			((TextField &) get("textField1")).setText(L"Test жопа");
			break;
		case 2: {
			const std::wstring message = ((TextField &) get("textField1")).getText();

			app->getClient()->sendString(message);

			std::wstringstream text;
			text << gConfig.name.c_str();
			text << L": ";
			text << message.c_str();
			text << "\n";

			((TextArea &) get("textArea1")).append(text.str());
			break;
		}
		case 3:
			app->getClient()->connectToServer(gConfig.name, gConfig.ip, gConfig.port);
			break;
		default:
			break;
	}
}
