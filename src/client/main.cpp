//
// Created by Igor on 2/6/2018.
//

#include <windows.h>
#include <fcntl.h>
#include <cstdio>
#include "ui/window.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int showCmd) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	MSG msg{ };

	ui::Window window(L"test тест", hInst, 800, 600, showCmd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}