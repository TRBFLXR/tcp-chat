//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CONNECTION_HPP
#define TCP_CHAT_CONNECTION_HPP

#include <winsock2.h>

#include <packetmanager.hpp>

struct Connection {
	explicit Connection(SOCKET socket) : socket(socket), id(0) { }

	SOCKET socket;
	PacketManager pm;
	int id;
};


#endif //TCP_CHAT_CONNECTION_HPP
