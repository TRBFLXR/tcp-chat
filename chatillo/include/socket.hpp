//
// Created by Igor on 2/8/2018.
//

#ifndef TCP_CHAT_SOCKET_HPP
#define TCP_CHAT_SOCKET_HPP

#include <connection.hpp>

class Socket {
protected:
	bool sendAll(const Connection &connection, const char *data, int size) const;
	bool receiveAll(const Connection &connection, char *data, int size) const;

	bool getInt(const Connection &connection, int &value) const;
	bool getPacketType(const Connection &connection, PacketType &packetType) const;
	bool getString(const Connection &connection, std::wstring &str) const;

	virtual bool processPacket(const Connection &connection, PacketType packetType) = 0;
};


#endif //TCP_CHAT_SOCKET_HPP
