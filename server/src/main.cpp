//
// Created by Igor on 2/6/2018.
//

#include <cstdio>
#include <fcntl.h>

#include "server.hpp"

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	printf("server\n");

	Server server(1111);
	while (true) {
		server.listenConnection();
	}

	system("pause");
	return EXIT_SUCCESS;
}