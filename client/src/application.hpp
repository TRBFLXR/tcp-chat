//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_APPLICATION_HPP
#define TCP_CHAT_APPLICATION_HPP

#include <packetstructure.hpp>
#include "client.hpp"
#include "ui/window.hpp"

class Application {
public:
	explicit Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd);
	~Application();

	int run();

	inline const ui::Window &getWindow() const { return window; }
	inline Client &getClient() { return client; }

	static void handleChatMessage(const std::wstring &sender, const std::wstring &message);

private:
	static Application *appPtr;

	MSG msg;

	Client client;
	ui::Window window;
};


#endif //TCP_CHAT_APPLICATION_HPP
