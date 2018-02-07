//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CLIENT_HPP
#define TCP_CHAT_CLIENT_HPP

#include <winsock2.h>
#include <string>
#include <thread>
#include <packetmanager.hpp>


class Client {
public:
	explicit Client(const std::string_view &ip, uint16_t port);
	~Client();

	bool connectToServer();
	void disconnect();

	void sendString(const std::wstring_view &str);

private:
	bool closeConnection();
	bool processPacket(PacketType packetType);

	static void clientThreadFunc(Client &client);
	static void packetSenderThreadFunc(Client &client);

	bool sendAll(const char *data, int dataSize);
	bool receiveAll(char *data, int dataSize);

	bool getInt(int &value);
	bool getPacketType(PacketType &packetType);
	bool getString(std::wstring &str);

private:
	bool terminateThreads;
	bool isConnected;

	SOCKET connection;
	SOCKADDR_IN addr;
	PacketManager pm;

	std::thread packetSenderThread;
	std::thread clientThread;
};


#endif //TCP_CHAT_CLIENT_HPP
