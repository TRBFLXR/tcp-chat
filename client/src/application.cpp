//
// Created by Igor on 2/7/2018.
//

#include "application.hpp"

Application *Application::appPtr;

Application::Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		window(this, title, app, width, height, cmd) {

	client.setChatMessageCallback(handleChatMessage);

	appPtr = this;
}

Application::~Application() {
	client.disconnect();
}

int Application::run() {
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

void Application::handleChatMessage(const std::wstring &message, const std::wstring &sender) {
	appPtr->window.getComponents()->textArea->append(sender + L": " + message + L"\n");
}