//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CLIENT_HPP
#define TCP_CHAT_CLIENT_HPP

#include <string>
#include <thread>
#include <socket.hpp>

class Client : public Socket {
public:
	explicit Client();
	~Client();

	bool connectToServer(const std::string_view &ip, uint16_t port);
	void disconnect();

	void sendString(const std::wstring_view &str)  const;

private:
	bool closeConnection();
	bool processPacket(const Connection &connection, PacketType packetType) override;

	static void clientThreadFunc(Client *client);
	static void packetSenderThreadFunc(Client *client);

private:
	bool terminateThreads;
	bool isConnected;

	Connection connection;

	SOCKADDR_IN addr;

	std::thread packetSenderThread;
	std::thread clientThread;
};


#endif //TCP_CHAT_CLIENT_HPP
