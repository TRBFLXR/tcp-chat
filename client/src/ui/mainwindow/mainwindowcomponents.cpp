//
// Created by Igor on 2/9/2018.
//

#include <sstream>
#include "../../application.hpp"
#include "mainwindowcomponents.hpp"

ui::MainWindowComponents::MainWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("buttonSend", new Button(L"Send", {20, 20}, {100, 20}, pHwnd, 1));
	add("buttonConnect", new Button(L"Connect", {20, 50}, {100, 20}, pHwnd, 2));
	add("buttonDisconnect", new Button(L"Disconnect", {20, 80}, {100, 20}, pHwnd, 3));
	add("textAreaChat", new TextArea({0, 120}, {500, 320}, pHwnd, 0));
	add("textFieldMessage", new TextField({130, 20}, {100, 20}, pHwnd, 0));
}

void ui::MainWindowComponents::input(WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case 1: {
			sendMessage();
			break;
		}
		case 2: {
			app->getClient()->connectToServer(gConfig.name, gConfig.ip, gConfig.port);
			break;
		}
		case 3:
			app->getClient()->disconnect();
			break;
		default:
			break;
	}
}

void ui::MainWindowComponents::sendMessage() {
	if (!app->getClient()->connected()) return;

	const std::wstring message = ((TextField &) get("textFieldMessage")).getText();
	if (message.empty()) return;

	app->getClient()->sendString(message);

	std::wstringstream text;
	text << gConfig.name.c_str();
	text << L": ";
	text << message.c_str();
	text << "\n";

	((TextArea &) get("textAreaChat")).append(text.str());
}
