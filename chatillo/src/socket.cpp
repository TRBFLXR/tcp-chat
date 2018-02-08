//
// Created by Igor on 2/8/2018.
//

#include <socket.hpp>

bool Socket::sendAll(std::shared_ptr<Connection> &connection, const char *data, int size) {
	int sended = 0;
	while (sended < size) {
		int ret = send(connection->socket, data + sended, size - sended, 0);
		if (ret == SOCKET_ERROR) return false;

		sended += ret;
	}

	return true;
}

bool Socket::receiveAll(std::shared_ptr<Connection> &connection, char *data, int size) {
	int received = 0;
	while (received < size) {
		int ret = recv(connection->socket, data + received, size - received, 0);
		if (ret == SOCKET_ERROR || ret == 0) return false;

		received += ret;
	}
	return true;
}

bool Socket::getInt(std::shared_ptr<Connection> &connection, int &value) {
	if (!receiveAll(connection, reinterpret_cast<char *>(&value), sizeof(int))) return false;

	value = (int) ntohl((u_long) value);
	return true;
}

bool Socket::getPacketType(std::shared_ptr<Connection> &connection, PacketType &packetType) {
	return getInt(connection, reinterpret_cast<int &>(packetType));
}

bool Socket::getString(std::shared_ptr<Connection> &connection, std::wstring &str) {
	int bufferSize;
	if (!getInt(connection, bufferSize)) return false;
	if (bufferSize == 0) return true;

	str.resize((size_t) bufferSize / sizeof(wchar_t));

	return receiveAll(connection, reinterpret_cast<char *>(str.data()), bufferSize);
}
