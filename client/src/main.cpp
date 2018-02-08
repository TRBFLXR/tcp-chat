//
// Created by Igor on 2/6/2018.
//

#include <fcntl.h>
#include <cstdio>
#include <iostream>

#include "application.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int showCmd) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	int exit = 0;

	try {
		Application app(L"test тест", hInst, 800, 600, showCmd);
		exit = app.run();
	} catch (std::exception &ex) {
		MessageBox(nullptr, reinterpret_cast<LPCWSTR>(ex.what()), L"Error", MB_OK | MB_ICONERROR);
	}

	return exit;
}