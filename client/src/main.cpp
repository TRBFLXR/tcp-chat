//
// Created by Igor on 2/6/2018.
//

#include <fcntl.h>
#include <cstdio>
#include <iostream>

#include "client.hpp"
#include "ui/window.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int showCmd) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

//	MSG msg{ };
//
//	ui::Window window(L"test тест", hInst, 800, 600, showCmd);
//
//	while (GetMessage(&msg, nullptr, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}

//	return static_cast<int>(msg.wParam);

	//"109.87.123.75"
	Client client("127.0.0.1", 1111);
	if (!client.connectToServer()) {
		fwprintf(stderr, L"Failed to connect...\n");

		system("pause");
		return 0;
	}

	std::wstring input;
	while (true) {
		std::getline(std::wcin, input);
		if (!input.empty()) {
			client.sendString(input);
		}
	}

	client.disconnect();

	return 0;
}