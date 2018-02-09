//
// Created by Igor on 2/7/2018.
//

#include <packetstructure.hpp>
#include "client.hpp"

Client::Client() : terminateThreads(false), isConnected(false) {
	WSADATA wsaData{ };
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) throw std::runtime_error("Winsock startup failed");
}

Client::~Client() {
	closeConnection();
	if (packetSenderThread.joinable()) {
		packetSenderThread.join();
	}
	if (clientThread.joinable()) {
		clientThread.join();
	}
}

bool Client::connectToServer(const std::wstring_view &name, const std::string_view &ip, uint16_t port) {
	addr.sin_addr.s_addr = inet_addr(ip.data());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	connection.id = 0;
	connection.name = name;
	connection.socket = socket(AF_INET, SOCK_STREAM, 0);

	int addrSize = sizeof(addr);
	if (connect(connection.socket, reinterpret_cast<const SOCKADDR *>(&addr), addrSize) != 0) {
		throw std::runtime_error("Failed to connect");
	}

	wprintf(L"Connected!\n");

	packetSenderThread = std::thread(packetSenderThreadFunc, this);
	packetSenderThread.detach();

	clientThread = std::thread(clientThreadFunc, this);
	clientThread.detach();

	ps::Register reg(name);
	connection.pm.push(reg.toPacket());

	isConnected = true;

	return true;
}

void Client::disconnect() {
	connection.pm.clear();
	closesocket(connection.socket);

	isConnected = false;

	wprintf(L"Disconnected\n");
}

bool Client::closeConnection() {
	terminateThreads = true;
	if (closesocket(connection.socket) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) return true;

		std::wstring err = L"Failed to close socket. Winsock Error: " + std::to_wstring(WSAGetLastError());
		MessageBox(nullptr, err.c_str(), L"Error", MB_OK | MB_ICONERROR);

		return false;
	}

	return true;
}

void Client::sendString(const std::wstring_view &str) const {
	ps::ChatMessage message(str);
	connection.pm.push(message.toPacket());
}

void Client::clientThreadFunc(Client *client) {
	PacketType PacketType;
	while (true) {
		if (client->terminateThreads) break;
		if (!client->getPacketType(client->connection, PacketType)) break;
		if (!client->processPacket(client->connection, PacketType)) break;
	}
	wprintf(L"Lost connection\n");

	client->terminateThreads = true;
	if (client->closeConnection()) {
		wprintf(L"Socket was closed successfully\n");
	} else {
		wprintf(L"Socket was not able to be closed\n");
	}
}

void Client::packetSenderThreadFunc(Client *client) {
	while (true) {
		if (client->terminateThreads) break;

		while (client->connection.pm.hasPackets()) {
			std::shared_ptr<Packet> p = client->connection.pm.pop();

			if (!client->sendAll(client->connection, p->getBuffer().data(), (int) p->getBuffer().size())) {
				wprintf(L"Failed to send packet to server...\n");
				break;
			}
		}
		Sleep(5);
	}

	wprintf(L"Packet thread closing...\n");
}

bool Client::processPacket(const Connection &connection, PacketType packetType) {
	switch (packetType) {
		case PacketType::ServerChatMessage: {
			std::wstring name;
			std::wstring message;
			if (!getString(connection, message)) return false;
			if (!getString(connection, name)) return false;

			chatMessageCallback(message, name);

			wprintf(L"%ls\n", message.c_str());

			break;
		}
		default:
			wprintf(L"Unrecognized PacketType: %i\n", packetType);
			break;
	}

	return true;
}