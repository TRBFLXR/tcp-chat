//
// Created by Igor on 2/8/2018.
//

#ifndef TCP_CHAT_SOCKET_HPP
#define TCP_CHAT_SOCKET_HPP

#include <connection.hpp>

class Socket {
protected:
	bool sendAll(std::shared_ptr<Connection> &connection, const char *data, int size);
	bool receiveAll(std::shared_ptr<Connection> &connection, char *data, int size);

	bool getInt(std::shared_ptr<Connection> &connection, int &value);
	bool getPacketType(std::shared_ptr<Connection> &connection, PacketType &packetType);
	bool getString(std::shared_ptr<Connection> &connection, std::wstring &str);

	virtual bool processPacket(std::shared_ptr<Connection> &connection, PacketType packetType) = 0;
};


#endif //TCP_CHAT_SOCKET_HPP
