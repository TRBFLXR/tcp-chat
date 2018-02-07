//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_SERVER_HPP
#define TCP_CHAT_SERVER_HPP

#include <winsock2.h>
#include <string>
#include <vector>
#include <shared_mutex>
#include <thread>

#include <connection.hpp>

class Server {
public:
	explicit Server(uint16_t port, bool loopBackToLH = false);
	~Server();

	bool listenConnection();

private:
	bool sendAll(std::shared_ptr<Connection> &connection, const char *data, int size);
	bool receiveAll(std::shared_ptr<Connection> &connection, char *data, int size);

	bool getInt(std::shared_ptr<Connection> &connection, int &value);
	bool getPacketType(std::shared_ptr<Connection> &connection, PacketType &packetType);
	bool getString(std::shared_ptr<Connection> &connection, std::wstring &str);

	bool processPacket(std::shared_ptr<Connection> &connection, PacketType packetType);

	static void clientHandlerThread(Server &server, std::shared_ptr<Connection> connection);
	static void packetSenderThread(Server &server);

	void disconnect(std::shared_ptr<Connection> &connection);

private:
	int idCounter;
	std::vector<std::shared_ptr<Connection>> connections;
	std::shared_mutex connectionMutex;

	SOCKADDR_IN addr;
	SOCKET listener;

	bool terminateThreads;
	std::vector<std::thread *> threads;
};


#endif //TCP_CHAT_SERVER_HPP