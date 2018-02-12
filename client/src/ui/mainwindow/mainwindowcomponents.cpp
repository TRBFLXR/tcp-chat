//
// Created by Igor on 2/9/2018.
//

#include <sstream>
#include "../../application.hpp"
#include "mainwindowcomponents.hpp"
#include "../components/listbox.hpp"

ui::MainWindowComponents *ui::MainWindowComponents::comPtr;

ui::MainWindowComponents::MainWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("buttonSend", new Button(L"Send", {505, 417}, {100, 26}, pHwnd, 1));
	add("buttonConnect", new Button(L"Connect", {610, 5}, {100, 20}, pHwnd, 2));
	add("buttonDisconnect", new Button(L"Disconnect", {715, 5}, {100, 20}, pHwnd, 3));
	add("textAreaChat", new TextArea({5, 5}, {600, 407}, pHwnd, 4, DEFAULT_TEXTAREA_STYLE | ES_READONLY));
	add("textFieldMessage", new TextField({5, 417}, {495, 26}, pHwnd, 5));
	add("listBoxUsers", new ListBox({610, 30}, {205, 390}, pHwnd, 6, DEFAULT_LISTBOX_STYLE | LBS_NOSEL));

	oldEditProc = (WNDPROC) SetWindowLongPtr((get("textFieldMessage")).getHwnd(), GWLP_WNDPROC, (LONG_PTR) subEditProc);

	comPtr = this;
}

void ui::MainWindowComponents::input(WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case 1: {
			sendMessage();

			SetFocus(((TextField &) get("textFieldMessage")).getHwnd());
			break;
		}
		case 2: {
			app->showLostConnection(true);
			if (!app->getClient()->connectToServer(gConfig.name, gConfig.ip, gConfig.port)) break;

			EnableWindow(((Button &) get("buttonConnect")).getHwnd(), FALSE);
			EnableWindow(((Button &) get("buttonSend")).getHwnd(), TRUE);
			EnableWindow(((Button &) get("buttonDisconnect")).getHwnd(), TRUE);
			EnableWindow(((TextField &) get("textFieldMessage")).getHwnd(), TRUE);

			SetFocus(((TextField &) get("textFieldMessage")).getHwnd());
			break;
		}
		case 3: {
			app->showLostConnection(false);
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

	((TextArea &) get("textAreaChat")).setText(L"");

	((ListBox &) get("listBoxUsers")).clear();
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

LRESULT ui::MainWindowComponents::subEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CHAR: {
			if (wParam == VK_RETURN) {
				comPtr->sendMessage();
				return 0;
			}
		}
		default:
			return CallWindowProc(comPtr->oldEditProc, hwnd, msg, wParam, lParam);
	}
}