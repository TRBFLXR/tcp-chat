//
// Created by Igor on 2/6/2018.
//

#include <cstdio>
#include <fcntl.h>
#include "../../chatillo/src/packet.hpp"

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	printf("server\n");

	Packet p;
	p.append(L"1234567890");
	p.append(L"ауе");
	p.append(123);

	auto &b = p.getBuffer();

	wprintf(L"size:%llu\n", b.size());
	wprintf(L"%ls\n", (wchar_t *) b.data());


//	system("pause");
	return EXIT_SUCCESS;
}