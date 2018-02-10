//
// Created by Igor on 2/7/2018.
//

#include <sstream>
#include "application.hpp"
#include "ui/components/textarea.hpp"

Application *Application::appPtr;

Application::Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		window(this, title, app, width, height, cmd),
		configWindow(this, L"Config", app, 170, 290, SW_HIDE) {

	client = new Client();

	client->setChatMessageCallback(handleChatMessage);
	client->setExceptionCallback(handleClientException);

	if (!Config::load(config)) {
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

void Application::handleChatMessage(const std::wstring &message, const std::wstring &sender) {
	std::wstringstream text;
	text << sender.c_str();
	text << L": ";
	text << message.c_str();
	text << "\n";

	((ui::TextArea &) appPtr->window.get("textArea1")).append(text.str());
}

void Application::handleClientException(const std::exception &ex) {
	MessageBoxA(appPtr->window.getHwnd(), ex.what(), "Error", MB_OK | MB_ICONERROR);
}

void Application::showConfigWindow() const {
	EnableWindow(window.getHwnd(), FALSE);
	configWindow.setShowCommand(SW_SHOW);
}
