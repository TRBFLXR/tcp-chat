//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CLIENT_HPP
#define TCP_CHAT_CLIENT_HPP

#include <winsock2.h>
#include <string>
#include <thread>
#include <socket.hpp>

class Client : public Socket {
public:
	explicit Client(const std::string_view &ip, uint16_t port);
	~Client();

	bool connectToServer();
	void disconnect();

	void sendString(const std::wstring_view &str);

private:
	bool closeConnection();
	bool processPacket(std::shared_ptr<Connection> &connection, PacketType packetType) override;

	static void clientThreadFunc(Client &client);
	static void packetSenderThreadFunc(Client &client);

private:
	bool terminateThreads;
	bool isConnected;

	std::shared_ptr<Connection> connection;

	SOCKADDR_IN addr;

	std::thread packetSenderThread;
	std::thread clientThread;
};


#endif //TCP_CHAT_CLIENT_HPP
