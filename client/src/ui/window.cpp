//
// Created by Igor on 2/6/2018.
//

#include <stdexcept>
#include "window.hpp"

ui::Window::Window(Application *application, const std::wstring_view &title, const std::wstring_view &className,
                   WNDPROC proc, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		application(application),
		title(title) {

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = proc;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className.data();
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hInstance = app;

	if (!RegisterClassExW(&wc)) throw std::runtime_error("Unable to register class");

	hwnd = CreateWindowW(
			className.data(),
			title.data(),
			WS_OVERLAPPEDWINDOW, //display mode
			CW_USEDEFAULT, //pos x
			CW_USEDEFAULT, // pos y
			width,
			height,
			nullptr, // parent
			nullptr, // menu
			HINSTANCE(app),
			nullptr);

	if (!hwnd) throw std::runtime_error("Unable to create window");

	ShowWindow(hwnd, cmd);
	UpdateWindow(hwnd);
}

ui::Window::~Window() {
	delete components;
}

void ui::Window::setTitle(const std::wstring_view &title) {
	Window::title = title;

	SetWindowText(hwnd, title.data());
}