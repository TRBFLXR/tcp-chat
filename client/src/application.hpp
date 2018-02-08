//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_APPLICATION_HPP
#define TCP_CHAT_APPLICATION_HPP

#include "client.hpp"
#include "ui/window.hpp"

class Application {
public:
	explicit Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd);
	~Application();

	int run();

	inline const ui::Window &getWindow() const { return window; }
	inline const Client &getClient() const { return client; }

private:
	MSG msg;

	Client client;
	ui::Window window;
};


#endif //TCP_CHAT_APPLICATION_HPP
