//
// Created by Igor on 2/7/2018.
//

#include "application.hpp"
#include "config.hpp"
#include "ui/components/textarea.hpp"

Application *Application::appPtr;

Application::Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		window(this, title, app, width, height, cmd),
		configWindow(this, L"Config", app, 170, 290, SW_HIDE) {

	client = new Client();

	client->setChatMessageCallback(handleChatMessage);

	Config config;
	if (Config::load(config)) {
		client->connectToServer(config.name, config.ip, config.port);
	} else {
		configWindow.setShowCommand(SW_SHOW);
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
	((ui::TextArea &) appPtr->window.get("textArea1")).append(sender + L": " + message + L"\n");
}