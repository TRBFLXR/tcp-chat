//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CONNECTION_HPP
#define TCP_CHAT_CONNECTION_HPP

#include <winsock2.h>
#include <string>
#include <packetmanager.hpp>

struct Connection {
	explicit Connection() = default;
	explicit Connection(SOCKET socket) : socket(socket), id(0) { }

	int id = 0;
	SOCKET socket{ };
	mutable bool selfDisconnect = true;
	mutable std::wstring name;
	mutable PacketManager pm{ };
};


#endif //TCP_CHAT_CONNECTION_HPP
