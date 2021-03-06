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

	addr.sin_addr.s_addr = loopBackToLH ? inet_addr("127.0.0.1") : htonl(INADDR_ANY);
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

	std::thread packetSender(packetSenderThread, this);
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

	//create user list packet
	std::vector<std::wstring *> users;
	for (auto &&c : connections) {
		users.push_back(&c->name);
	}
	ps::UserList ul(users);
	std::shared_ptr<Packet> usersList = std::make_shared<Packet>(ul.toPacket());

	//lock
	std::lock_guard<std::shared_mutex> lock(connectionMutex);

	std::shared_ptr<Connection> connection(std::make_shared<Connection>(connectionSocket));
	connections.push_back(connection);

	connection->id = idCounter;
	++idCounter;

	wprintf(L"Client connected id:%i\n", connection->id);

	//send users list
	connection->pm.push(usersList);

	std::thread clientThread(clientHandlerThread, this, connection);
	clientThread.detach();
	threads.push_back(&clientThread);

	users.clear();
	return true;
}

void Server::disconnect(const Connection &connection) {
	std::lock_guard<std::shared_mutex> lock(connectionMutex);

	connection.pm.clear();
	closesocket(connection.socket);

	//delete from vector
	for (size_t i = 0; i < connections.size(); ++i) {
		if (connections[i]->id == connection.id) {
			connections.erase(connections.begin() + i);
		}
	}

	wprintf(L"Cleaned up client %i\n", connection.id);
	wprintf(L"Total connections: %llu\n", connections.size());
}

void Server::clientHandlerThread(Server *server, std::shared_ptr<Connection> connection) {
	PacketType packetType{ };

	while (true) {
		if (server->terminateThreads) break;
		if (!server->getPacketType(*connection, packetType)) break;
		if (!server->processPacket(*connection, packetType)) break;
	}

	if (connection->selfDisconnect) {
		ps::Disconnect d(connection->name);
		std::shared_ptr<Packet> disconnect = std::make_shared<Packet>(d.toPacket());
		server->sendPacketToAll(connection->id, disconnect);
	} else {
		ps::DuplicateName d;
		Packet dp = *d.toPacket();

		std::shared_lock<std::shared_mutex> lock(server->connectionMutex);
		if (!server->sendAll(*connection, dp.getBuffer().data(), (int) dp.getBuffer().size())) {
			fwprintf(stderr, L"Failed to send packet to id:%i\n", connection->id);
		}
	}

	wprintf(L"Client disconnected (id:%i)\n", connection->id);
	server->disconnect(*connection);
}

void Server::packetSenderThread(Server *server) {
	while (true) {
		if (server->terminateThreads) break;

		std::shared_lock<std::shared_mutex> lock(server->connectionMutex);
		for (auto &&c : server->connections) {
			if (c->pm.hasPackets()) {
				std::shared_ptr<Packet> p = c->pm.pop();
				if (!server->sendAll(*c, p->getBuffer().data(), (int) p->getBuffer().size())) {
					fwprintf(stderr, L"Failed to send packet to id:%i\n", c->id);
				}
			}
		}
		Sleep(5);
	}
	wprintf(L"Ending packet sending thread...\n");
}

bool Server::processPacket(const Connection &connection, PacketType packetType) {
	switch (packetType) {
		case PacketType::Connect: {
			if (!getString(connection, connection.name)) return false;

			for (auto &&c : connections) {
				if (c->id == connection.id) continue;
				if (wcscmp(c->name.c_str(), connection.name.c_str()) == 0) {
					connection.selfDisconnect = false;
					return false;
				}
			}

			ps::Connect r(connection.name);
			std::shared_ptr<Packet> regPacket = std::make_shared<Packet>(r.toPacket());
			sendPacketToAll(connection.id, regPacket);
			break;
		}

		case PacketType::ChatMessage: {
			std::wstring message;
			if (!getString(connection, message)) return false;

			ps::ServerChatMessage cm(message, connection.name);
			std::shared_ptr<Packet> msgPacket = std::make_shared<Packet>(cm.toPacket());
			sendPacketToAll(connection.id, msgPacket);

			wprintf(L"Processed message from %ls(%i): %ls\n", connection.name.c_str(), connection.id, message.c_str());
			break;
		}
		default:
			fwprintf(stderr, L"Unrecognized packet: %i\n", packetType);
			return false;
	}

	return true;
}

void Server::sendPacketToAll(int sender, const std::shared_ptr<Packet> &packet) {
	std::shared_lock<std::shared_mutex> lock(connectionMutex);
	for (auto &&c : connections) {
		if (c->id == sender) continue;

		c->pm.push(packet);
	}
}