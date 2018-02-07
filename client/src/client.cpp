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
	connection = socket(AF_INET, SOCK_STREAM, 0);

	int addrSize = sizeof(addr);
	if (connect(connection, reinterpret_cast<const SOCKADDR *>(&addr), addrSize) != 0) {
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
	pm.clear();
	closesocket(connection);

	wprintf(L"Disconnected\n");
}

bool Client::closeConnection() {
	terminateThreads = true;
	if (closesocket(connection) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) return true;

		std::wstring err = L"Failed to close socket. Winsock Error: " + std::to_wstring(WSAGetLastError());
		MessageBox(nullptr, err.c_str(), L"Error", MB_OK | MB_ICONERROR);

		return false;
	}

	return true;
}

void Client::sendString(const std::wstring_view &str) {
	ps::ChatMessage message(str);
	pm.push(message.toPacket());
}

bool Client::sendAll(const char *data, int dataSize) {
	int sended = 0;
	while (sended < dataSize) {
		int ret = send(connection, data + sended, dataSize - sended, 0);
		if (ret == SOCKET_ERROR) return false;

		sended += ret;
	}

	return true;
}

bool Client::receiveAll(char *data, int dataSize) {
	int received = 0;
	while (received < dataSize) {
		int ret = recv(connection, data + received, dataSize - received, 0);
		if (ret == SOCKET_ERROR || ret == 0) return false;

		received += ret;
	}

	return true;
}

bool Client::getInt(int &value) {
	if (!receiveAll(reinterpret_cast<char *>(&value), sizeof(int))) return false;
	value = (int) ntohl((u_long) value);

	return true;
}

bool Client::getPacketType(PacketType &packetType) {
	return getInt(reinterpret_cast<int &>(packetType));
}

bool Client::getString(std::wstring &str) {
	int bufferSize;
	if (!getInt(bufferSize)) return false;
	if (bufferSize == 0) return true;

	str.resize((size_t) bufferSize / sizeof(wchar_t));

	return receiveAll(reinterpret_cast<char *>(str.data()), bufferSize);
}

void Client::clientThreadFunc(Client &client) {
	PacketType PacketType;
	while (true) {
		if (client.terminateThreads) break;
		if (!client.getPacketType(PacketType)) break;
		if (!client.processPacket(PacketType)) break;
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

		while (client.pm.hasPackets()) {
			std::shared_ptr<Packet> p = client.pm.pop();

			if (!client.sendAll(p->getBuffer().data(), (int) p->getBuffer().size())) {
				wprintf(L"Failed to send packet to server...\n");
				break;
			}
		}
		Sleep(5);
	}

	wprintf(L"Packet thread closing...\n");
}

bool Client::processPacket(PacketType packetType) {
	switch (packetType) {
		case PacketType::ChatMessage: {
			std::wstring message;
			if (!getString(message)) return false;

			wprintf(L"%ls\n", message.c_str());

			break;
		}
		default:
			wprintf(L"Unrecognized PacketType: %i\n", packetType);
			break;
	}

	return true;
}