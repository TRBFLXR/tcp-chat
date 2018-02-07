//
// Created by Igor on 2/7/2018.
//

#include <algorithm>
#include <packetstructure.hpp>
#include "server.hpp"

Server::Server(uint16_t port, bool loopBackToLH) : idCounter(0), terminateThreads(false) {
	WSADATA wsaData{ };
	WORD dllVersion = MAKEWORD(2, 1);

	if (WSAStartup(dllVersion, &wsaData) != 0) {
		fwprintf(stderr, L"Winsock startup failed\n");

		system("pause");
		exit(EXIT_FAILURE);
	}

	addr.sin_addr.s_addr = loopBackToLH ? htonl(INADDR_ANY) : inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(listener, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr)) == SOCKET_ERROR) {
		fwprintf(stderr, L"Failed to bind socket. Winsock err: %i\n", WSAGetLastError());

		system("pause");
		exit(EXIT_FAILURE);
	}
	if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
		fwprintf(stderr, L"Failed to listen on socket. Winsock err: %i\n", WSAGetLastError());

		system("pause");
		exit(EXIT_FAILURE);
	}

	std::thread packetSender(packetSenderThread, std::ref(*this));
	packetSender.detach();
	threads.push_back(&packetSender);
}

Server::~Server() {
	terminateThreads = true;
	for (std::thread *thread : threads) {
		thread->join();
	}
}

bool Server::listenConnection() {
	int addrSize = sizeof(addr);
	SOCKET connectionSocket = accept(listener, reinterpret_cast<SOCKADDR *>(&addr), &addrSize);

	if (!connectionSocket) {
		fwprintf(stderr, L"Failed to accept connection.\n");
		return false;
	}

	std::lock_guard<std::shared_mutex> lock(connectionMutex);

	std::shared_ptr<Connection> connection(std::make_shared<Connection>(connectionSocket));
	connections.push_back(connection);

	connection->id = idCounter;
	++idCounter;

	wprintf(L"Client connected id:%i\n", connection->id);

	std::thread clientThread(clientHandlerThread, std::ref(*this), connection);
	clientThread.detach();
	threads.push_back(&clientThread);

	return true;
}

void Server::disconnect(std::shared_ptr<Connection> &connection) {
	std::lock_guard<std::shared_mutex> lock(connectionMutex);

	connection->pm.clear();
	closesocket(connection->socket);

	connections.erase(std::remove(connections.begin(), connections.end(), connection));

	wprintf(L"Cleaned up client %i\n", connection->id);
	wprintf(L"Total connections: %llu\n", connections.size());
}

void Server::clientHandlerThread(Server &server, std::shared_ptr<Connection> connection) {
	PacketType packetType{ };

	while (true) {
		if (server.terminateThreads) break;
		if (!server.getPacketType(connection, packetType)) break;
		if (!server.processPacket(connection, packetType)) break;
	}

	wprintf(L"Client disconnected (id:%i)\n", connection->id);
	server.disconnect(connection);
}

void Server::packetSenderThread(Server &server) {
	while (true) {
		if (server.terminateThreads) break;

		std::shared_lock<std::shared_mutex> lock(server.connectionMutex);
		for (auto &&c : server.connections) {
			if (c->pm.hasPackets()) {
				std::shared_ptr<Packet> p = c->pm.pop();
				if (!server.sendAll(c, p->getBuffer().data(), (int) p->getBuffer().size())) {
					fwprintf(stderr, L"Failed to send packet to id:%i\n", c->id);
				}
			}
		}
		Sleep(5);
	}
	wprintf(L"Ending packet sending thread...\n");
}

bool Server::sendAll(std::shared_ptr<Connection> &connection, const char *data, const int size) {
	int sended = 0;
	while (sended < size) {
		int ret = send(connection->socket, data + sended, size - sended, 0);
		if (ret == SOCKET_ERROR) return false;

		sended += ret;
	}

	return true;
}

bool Server::receiveAll(std::shared_ptr<Connection> &connection, char *data, int size) {
	int received = 0;
	while (received < size) {
		int ret = recv(connection->socket, data + received, size - received, 0);
		if (ret == SOCKET_ERROR || ret == 0) return false;

		received += ret;
	}
	return true;
}

bool Server::getInt(std::shared_ptr<Connection> &connection, int &value) {
	if (!receiveAll(connection, reinterpret_cast<char *>(&value), sizeof(int))) return false;

	value = (int) ntohl((u_long) value);
	return true;
}

bool Server::getPacketType(std::shared_ptr<Connection> &connection, PacketType &packetType) {
	return getInt(connection, reinterpret_cast<int &>(packetType));
}

bool Server::getString(std::shared_ptr<Connection> &connection, std::wstring &str) {
	int bufferSize;
	if (!getInt(connection, bufferSize)) return false;
	if (bufferSize == 0) return true;

	str.resize((size_t) bufferSize / sizeof(wchar_t));

	return receiveAll(connection, reinterpret_cast<char *>(str.data()), bufferSize);
}

bool Server::processPacket(std::shared_ptr<Connection> &connection, PacketType packetType) {
	switch (packetType) {
		case PacketType::ChatMessage: {
			std::wstring message;
			if (!getString(connection, message)) return false;

			ps::ChatMessage cm(message);
			std::shared_ptr<Packet> msgPacket = std::make_shared<Packet>(cm.toPacket());
			{
				std::shared_lock<std::shared_mutex> lock(connectionMutex);
				for (auto &&c : connections) {
					if (c == connection) continue;

					c->pm.push(msgPacket);
				}
			}
			wprintf(L"Processed chat message packet from user(%i): %ls\n", connection->id, message.c_str());
			break;
		}
		default:
			fwprintf(stderr, L"Unrecognized packet: %i\n", packetType);
			return false;
	}

	return true;
}


