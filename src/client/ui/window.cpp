//
// Created by Igor on 2/6/2018.
//

#include <stdexcept>
#include "window.hpp"

ui::Window *ui::Window::windowPtr;

ui::Window::Window(const std::wstring_view &title, HINSTANCE app, unsigned width, unsigned height, int cmd) :
		title(title) {

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = inputProcessor;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"MainWindow";
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hInstance = app;

	if (!RegisterClassExW(&wc)) {
		throw std::runtime_error("Unable to register class");
	}

	hwnd = CreateWindowW(
			L"MainWindow",
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

	if (!hwnd) {
		throw std::runtime_error("Unable to create window");
	}

	ShowWindow(hwnd, cmd);
	UpdateWindow(hwnd);

	components = new Components(hwnd);

	windowPtr = this;
}

ui::Window::~Window() {
	delete components;
}

LRESULT ui::Window::inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:

			break;
		case WM_COMMAND: {
			windowPtr->components->input(LOWORD(wParam));
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void ui::Window::setTitle(const std::wstring_view &title) {
	Window::title = title;

	SetWindowText(hwnd, title.data());
}