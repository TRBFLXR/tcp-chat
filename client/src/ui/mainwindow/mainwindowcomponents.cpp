//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "mainwindowcomponents.hpp"
#include "../../config.hpp"

ui::MainWindowComponents::MainWindowComponents(Application *app) : Components(app) {
	HWND parent = app->getWindow().getHwnd();

	add("button1", new Button(L"button1", {20, 20}, {100, 20}, parent, 1));
	add("button2", new Button(L"button2", {20, 50}, {100, 20}, parent, 2));
	add("button3", new Button(L"button3", {20, 80}, {100, 20}, parent, 3));
	add("textArea1", new TextArea(L"", {0, 120}, {500, 320}, parent, 0));
	add("textField1", new TextField(L"", {130, 20}, {100, 20}, parent, 0));
}

void ui::MainWindowComponents::input(WORD id) {
	switch (id) {
		case 1:
			((TextField &) get("textField1")).setText(L"Test жопа");
			break;
		case 2: {
			const std::wstring message = ((TextField &) get("textField1")).getText();

			app->getClient()->sendString(message);
			((TextArea &) get("textArea1")).append(gConfig.name + L": " + message + L"\n");
			break;
		}
		case 3:
			app->getClient()->connectToServer(((TextField &) get("textField1")).getText(), "109.87.123.75", 1111);
			break;
		default:
			break;
	}
}
