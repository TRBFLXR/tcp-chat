//
// Created by Igor on 2/6/2018.
//

#include <stdexcept>
#include "window.hpp"

ui::Window::Window(Application *application, const std::wstring_view &title) : application(application), title(title) { }

ui::Window::~Window() {
	delete components;
}

void ui::Window::setTitle(const std::wstring_view &title) {
	Window::title = title;

	SetWindowText(hwnd, title.data());
}

void ui::Window::setShowCommand(int cmd) const {
	ShowWindow(hwnd, cmd);
	UpdateWindow(hwnd);
}
