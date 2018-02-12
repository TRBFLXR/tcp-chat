//
// Created by Igor on 2/7/2018.
//

#include <sstream>
#include "application.hpp"
#include "ui/components/textarea.hpp"
#include "ui/components/listbox.hpp"

Application *Application::appPtr;

Application::Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		window(this, title, app, width, height, cmd),
		configWindow(this, L"Config", app, 170, 290, SW_HIDE),
		hInstance(app),
		shouldExit(false),
		showLostConnectionMsg(true) {

	client = new Client();

	client->setUserConnectCallback(userConnected);
	client->setUserDisconnectCallback(userDisconnected);
	client->setChatMessageCallback(chatMessage);
	client->setExceptionCallback(clientException);
	client->setLostConnectionCallback(lostConnection);
	client->setUsersListCallback(usersList);
	client->setDuplicateNameCallback(onDuplicateName);

	if (!Config::load(config)) {
		shouldExit = true;
		showConfigWindow();
	}

	appPtr = this;
}

Application::~Application() {
	client->disconnect();

	delete client;
}

int Application::run() {
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

void Application::showConfigWindow() {
	EnableWindow(window.getHwnd(), FALSE);
	configWindow.setShowCommand(SW_SHOW);
	configWindow.onCreate();
}

void Application::userConnected(const std::wstring &name) {
	std::wstringstream text;
	text << L"User ";
	text << name.c_str();
	text << L" connected!\r\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
	((ui::ListBox &) appPtr->window.get("listBoxUsers")).addItem(name);
}

void Application::userDisconnected(const std::wstring &name) {
	std::wstringstream text;
	text << L"User ";
	text << name.c_str();
	text << L" disconnected!\r\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
	((ui::ListBox &) appPtr->window.get("listBoxUsers")).removeItem(name);
}

void Application::chatMessage(const std::wstring &message, const std::wstring &sender) {
	PlaySound(L"msg.wav", nullptr, SND_FILENAME | SND_ASYNC);

	std::wstringstream text;
	text << sender.c_str();
	text << L": ";
	text << message.c_str();
	text << "\r\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
}

void Application::clientException(const std::exception &ex) {
	MessageBoxA(appPtr->window.getHwnd(), ex.what(), "Error", MB_OK | MB_ICONERROR);
}

void Application::lostConnection() {
	appPtr->window.getComponents()->onCreate();

	if (appPtr->showLostConnectionMsg) {
		MessageBox(appPtr->window.getHwnd(), L"Lost connection...", L"Error", MB_OK | MB_ICONERROR);
	}
}

void Application::usersList(std::vector<std::wstring *> &users) {
	for (auto &&u : users) {
		((ui::ListBox &) appPtr->window.get("listBoxUsers")).addItem(*u);
	}
}

void Application::onDuplicateName() {
	appPtr->showLostConnectionMsg = false;
	MessageBox(appPtr->window.getHwnd(), L"Name already taken", L"Error", MB_OK | MB_ICONERROR);
}
