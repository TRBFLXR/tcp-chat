//
// Created by Igor on 2/9/2018.
//

#include "mainwindow.hpp"
#include "mainwindowcomponents.hpp"

ui::MainWindow *ui::MainWindow::windowPtr;

ui::MainWindow::MainWindow(Application *application, const std::wstring_view &title,
                           HINSTANCE app, unsigned width, unsigned height, int cmd) :
		Window(application, title, L"ConfigWindowClass", inputProcessor, app, width, height, cmd) {

	setupComponents();

	windowPtr = this;
}

ui::MainWindow::~MainWindow() { }

void ui::MainWindow::setupComponents() {
	components = new MainWindowComponents(application);
}

LRESULT ui::MainWindow::inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:
			break;

		case WM_COMMAND:
			windowPtr->components->input(LOWORD(wParam));
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
