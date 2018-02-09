//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_CLIENT_HPP
#define TCP_CHAT_CLIENT_HPP

#include <string>
#include <thread>
#include <socket.hpp>
#include <functional>
#include <utility>

class Client : public Socket {
public:
	explicit Client();
	~Client();

	bool connectToServer(const std::wstring_view &name, const std::string_view &ip, uint16_t port);
	void disconnect();

	void sendString(const std::wstring_view &str) const;

	inline void setName(const std::wstring_view &name) { connection.name = name; }

	inline void setChatMessageCallback(std::function<void(const std::wstring &, const std::wstring &)> callback) {
		chatMessageCallback = std::move(callback);
	}

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

	std::function<void(const std::wstring &, const std::wstring &)> chatMessageCallback;
};


#endif //TCP_CHAT_CLIENT_HPP
