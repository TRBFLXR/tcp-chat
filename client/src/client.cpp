//
// Created by Igor on 2/7/2018.
//

#include <packetstructure.hpp>
#include "client.hpp"

Client::Client(const std::string_view &ip, uint16_t port) : terminateThreads(false), isConnected(false) {
	WSADATA wsaData{ };
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBox(nullptr, L"Winsock startup failed", L"Error", MB_OK | MB_ICONERROR);

		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(ip.data());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
}

Client::~Client() {
	closeConnection();
	packetSenderThread.join();
	clientThread.join();
}

bool Client::connectToServer() {
	connection->id = 0;
	connection->socket = socket(AF_INET, SOCK_STREAM, 0);

	int addrSize = sizeof(addr);
	if (connect(connection->socket, reinterpret_cast<const SOCKADDR *>(&addr), addrSize) != 0) {
		MessageBox(nullptr, L"Failed to Connect", L"Error", MB_OK | MB_ICONERROR);

		return false;
	}

	wprintf(L"Connected!\n");

	packetSenderThread = std::thread(packetSenderThreadFunc, std::ref(*this));
	packetSenderThread.detach();

	clientThread = std::thread(clientThreadFunc, std::ref(*this));
	clientThread.detach();

	return true;
}

void Client::disconnect() {
	connection->pm.clear();
	closesocket(connection->socket);

	wprintf(L"Disconnected\n");
}

bool Client::closeConnection() {
	terminateThreads = true;
	if (closesocket(connection->socket) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) return true;

		std::wstring err = L"Failed to close socket. Winsock Error: " + std::to_wstring(WSAGetLastError());
		MessageBox(nullptr, err.c_str(), L"Error", MB_OK | MB_ICONERROR);

		return false;
	}

	return true;
}

void Client::sendString(const std::wstring_view &str) {
	ps::ChatMessage message(str);
	connection->pm.push(message.toPacket());
}

void Client::clientThreadFunc(Client &client) {
	PacketType PacketType;
	while (true) {
		if (client.terminateThreads) break;
		if (!client.getPacketType(client.connection, PacketType)) break;
		if (!client.processPacket(client.connection, PacketType)) break;
	}
	wprintf(L"Lost connection\n");

	client.terminateThreads = true;
	if (client.closeConnection()) {
		wprintf(L"Socket was closed successfully\n");
	} else {
		wprintf(L"Socket was not able to be closed\n");
	}
}

void Client::packetSenderThreadFunc(Client &client) {
	while (true) {
		if (client.terminateThreads) break;

		while (client.connection->pm.hasPackets()) {
			std::shared_ptr<Packet> p = client.connection->pm.pop();

			if (!client.sendAll(client.connection, p->getBuffer().data(), (int) p->getBuffer().size())) {
				wprintf(L"Failed to send packet to server...\n");
				break;
			}
		}
		Sleep(5);
	}

	wprintf(L"Packet thread closing...\n");
}

bool Client::processPacket(std::shared_ptr<Connection> &connection, PacketType packetType) {
	switch (packetType) {
		case PacketType::ChatMessage: {
			std::wstring message;
			if (!getString(connection, message)) return false;

			wprintf(L"%ls\n", message.c_str());

			break;
		}
		default:
			wprintf(L"Unrecognized PacketType: %i\n", packetType);
			break;
	}

	return true;
}