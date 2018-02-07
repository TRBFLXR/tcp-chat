//
// Created by Igor on 2/6/2018.
//

#include <winsock2.h>
#include <packet.hpp>

Packet::Packet(const char *buffer, int size) {
	append(buffer, size);
}

Packet::Packet(const PacketType &packetType) {
	append(packetType);
}


Packet::Packet(const std::shared_ptr<Packet> &other) {
	append(other->buffer.data(), (int)other->buffer.size());
}

void Packet::append(const PacketType &packetType) {
	append((int) packetType);
}

void Packet::append(int value) {
	const int v = (int) htonl((u_long) value);
	append(reinterpret_cast<const char *>(&v), sizeof(int));
}

void Packet::append(const std::wstring_view &string) {
	append(reinterpret_cast<const char *>(string.data()), (int) string.size() * sizeof(wchar_t));
}

void Packet::append(const char *data, int dataSize) {
	buffer.insert(buffer.end(), data, data + dataSize);
}