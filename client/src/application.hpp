//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_APPLICATION_HPP
#define TCP_CHAT_APPLICATION_HPP

#include "ui/window.hpp"

class Application {
public:
	explicit Application(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd);

	int run();

	inline const ui::Window &getWindow() const { return window; }

private:
	MSG msg;

	ui::Window window;
};


#endif //TCP_CHAT_APPLICATION_HPP
