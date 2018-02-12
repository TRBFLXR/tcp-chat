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

	inline bool connected() const { return isConnected; }

	inline void setUserConnectCallback(std::function<void(const std::wstring &)> callback) {
		userConnectCallback = std::move(callback);
	}

	inline void setUserDisconnectCallback(std::function<void(const std::wstring &)> callback) {
		userDisconnectCallback = std::move(callback);
	}

	inline void setChatMessageCallback(std::function<void(const std::wstring &, const std::wstring &)> callback) {
		chatMessageCallback = std::move(callback);
	}

	inline void setExceptionCallback(std::function<void(const std::exception &)> callback) {
		showException = std::move(callback);
	}

	inline void setLostConnectionCallback(std::function<void(void)> callback) {
		lostConnectionCallback = std::move(callback);
	}

	inline void setUsersListCallback(std::function<void(std::vector<std::wstring *> &)> callback) {
		usersListCallback = std::move(callback);
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

	std::function<void(void)> lostConnectionCallback;
	std::function<void(const std::wstring &)> userConnectCallback;
	std::function<void(const std::wstring &)> userDisconnectCallback;
	std::function<void(const std::wstring &, const std::wstring &)> chatMessageCallback;
	std::function<void(const std::exception &)> showException;
	std::function<void(std::vector<std::wstring *> &)> usersListCallback;
};


#endif //TCP_CHAT_CLIENT_HPP
