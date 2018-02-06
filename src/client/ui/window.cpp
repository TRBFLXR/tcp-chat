//
// Created by Igor on 2/6/2018.
//

#include <stdexcept>
#include "window.hpp"
#include "components/button.hpp"

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

	components.push_back(std::make_unique<Button>([&]() {
		MessageBeep(MB_ICONERROR);
		MessageBox(hwnd, L"clicked1", L"title", MB_OK);
	}, L"button1", vec2u(20, 20), vec2u(100, 20), hwnd, 1));

	components.push_back(std::make_unique<Button>([&]() {
		MessageBeep(MB_ICONERROR);
		MessageBox(hwnd, L"clicked2", L"title", MB_OK);
	}, L"button2", vec2u(20, 50), vec2u(100, 20), hwnd, 2));

	windowPtr = this;
}

ui::Window::~Window() { }

LRESULT ui::Window::inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:

			break;
		case WM_COMMAND: {
			Event event(LOWORD(wParam));

			for (int i = 0; i < windowPtr->components.size() && !event.isHandled(); ++i) {
				windowPtr->components[i]->handleEvent(event);
			}

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