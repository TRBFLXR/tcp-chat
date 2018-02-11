//
// Created by Igor on 2/7/2018.
//

#include <sstream>
#include "application.hpp"
#include "ui/components/textarea.hpp"

Application *Application::appPtr;

Application::Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		window(this, title, app, width, height, cmd),
		configWindow(this, L"Config", app, 170, 290, SW_HIDE),
		hInstance(app),
		shouldExit(false),
		showLostConnectionMsg(true) {

	client = new Client();

	client->setUserConnectCallback(handleUserConnect);
	client->setUserDisconnectCallback(handleUserDisconnect);
	client->setChatMessageCallback(handleChatMessage);
	client->setExceptionCallback(handleClientException);
	client->setLostConnectionCallback(handleLostConnection);

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

void Application::handleUserConnect(const std::wstring &name) {
	std::wstringstream text;
	text << L"User \n";
	text << name.c_str();
	text << L" connected!\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
}

void Application::handleUserDisconnect(const std::wstring &name) {
	std::wstringstream text;
	text << L"User \n";
	text << name.c_str();
	text << L" disconnected!\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
}

void Application::handleChatMessage(const std::wstring &message, const std::wstring &sender) {
	std::wstringstream text;
	text << sender.c_str();
	text << L": ";
	text << message.c_str();
	text << "\n";

	((ui::TextArea &) appPtr->window.get("textAreaChat")).append(text.str());
}

void Application::handleClientException(const std::exception &ex) {
	MessageBoxA(appPtr->window.getHwnd(), ex.what(), "Error", MB_OK | MB_ICONERROR);
}

void Application::handleLostConnection() {
	appPtr->window.getComponents()->onCreate();

	if (appPtr->showLostConnectionMsg) {
		MessageBox(appPtr->window.getHwnd(), L"Lost connection...", L"Error", MB_OK | MB_ICONERROR);
	}
}