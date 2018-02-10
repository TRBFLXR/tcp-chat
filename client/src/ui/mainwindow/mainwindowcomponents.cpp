//
// Created by Igor on 2/9/2018.
//

#include <sstream>
#include "../../application.hpp"
#include "mainwindowcomponents.hpp"

ui::MainWindowComponents::MainWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("buttonSend", new Button(L"Send", {505, 410}, {100, 26}, pHwnd, 1));
	add("buttonConnect", new Button(L"Connect", {610, 5}, {100, 20}, pHwnd, 2));
	add("buttonDisconnect", new Button(L"Disconnect", {715, 5}, {100, 20}, pHwnd, 3));
	add("textAreaChat", new TextArea({5, 5}, {600, 400}, pHwnd, 0, DEFAULT_TEXTAREA_STYLE | ES_READONLY));
	add("textFieldMessage", new TextField({5, 410}, {495, 26}, pHwnd, 0));
}

void ui::MainWindowComponents::input(WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case 1: {
			sendMessage();
			break;
		}
		case 2: {
			app->getClient()->connectToServer(gConfig.name, gConfig.ip, gConfig.port);
			EnableWindow(((Button &) get("buttonConnect")).getHwnd(), FALSE);
			EnableWindow(((Button &) get("buttonSend")).getHwnd(), TRUE);
			EnableWindow(((Button &) get("buttonDisconnect")).getHwnd(), TRUE);
			EnableWindow(((TextField &) get("textFieldMessage")).getHwnd(), TRUE);
			break;
		}
		case 3: {
			app->getClient()->disconnect();
			EnableWindow(((Button &) get("buttonConnect")).getHwnd(), TRUE);
			EnableWindow(((Button &) get("buttonSend")).getHwnd(), FALSE);
			EnableWindow(((Button &) get("buttonDisconnect")).getHwnd(), FALSE);
			EnableWindow(((TextField &) get("textFieldMessage")).getHwnd(), FALSE);
			break;
		}
		default:
			break;
	}
}

void ui::MainWindowComponents::onCreate() {
	EnableWindow(((TextField &) get("textFieldMessage")).getHwnd(), FALSE);
	EnableWindow(((Button &) get("buttonConnect")).getHwnd(), TRUE);
	EnableWindow(((Button &) get("buttonSend")).getHwnd(), FALSE);
	EnableWindow(((Button &) get("buttonDisconnect")).getHwnd(), FALSE);

	((TextField &) get("textFieldMessage")).setFont(L"SansSerif", 18);
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

	((TextField &) get("textFieldMessage")).setText(L"");
}
