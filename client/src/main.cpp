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
		Application app(L"ЖОПА", hInst, 827, 500, showCmd);
		exit = app.run();

	} catch (const std::exception &ex) {
		const char *err = ex.what();
		size_t size = strlen(err);

		std::wstring w_err(size, L'#');
		mbstowcs(&w_err[0], err , size);

		MessageBox(nullptr, w_err.c_str(), L"Error", MB_OK | MB_ICONERROR);
	}

	return exit;
}