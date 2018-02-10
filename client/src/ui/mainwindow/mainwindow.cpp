//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "mainwindowcomponents.hpp"

ui::MainWindow *ui::MainWindow::windowPtr;

ui::MainWindow::MainWindow(Application *application, const std::wstring_view &title,
                           HINSTANCE app, unsigned width, unsigned height, int cmd) :
		Window(application, title) {

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = inputProcessor;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"MainWindowClass";
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hInstance = app;

	if (!RegisterClassExW(&wc)) throw std::runtime_error("Unable to register class");

	hwnd = CreateWindowW(L"MainWindowClass", title.data(),
	                     WS_OVERLAPPEDWINDOW,
	                     CW_USEDEFAULT, CW_USEDEFAULT, width, height,
	                     nullptr, nullptr, app, nullptr);

	if (!hwnd) throw std::runtime_error("Unable to create window");

	setShowCommand(cmd);

	setupComponents();

	windowPtr = this;

	components->onCreate();
}

ui::MainWindow::~MainWindow() { }

void ui::MainWindow::setupComponents() {
	components = new MainWindowComponents(application, this);

	HMENU hMenu = CreateMenu();
	HMENU hFile = CreateMenu();
	HMENU hOptions = CreateMenu();

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFile, L"File");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hOptions, L"Options");

	AppendMenu(hFile, MF_STRING, 1001, L"Disconnect");
	AppendMenu(hFile, MF_STRING, 1002, L"Exit");

	AppendMenu(hOptions, MF_STRING, 1003, L"Configure");

	SetMenu(getHwnd(), hMenu);
}

LRESULT ui::MainWindow::inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_COMMAND:
			windowPtr->components->input(wParam);
			switch (LOWORD(wParam)) {
				case 1001:
					windowPtr->application->getClient()->disconnect();
					break;
				case 1002:
					DestroyWindow(windowPtr->getHwnd());
					break;
				case 1003:
					windowPtr->application->showConfigWindow();
					break;
				default:
					break;
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
