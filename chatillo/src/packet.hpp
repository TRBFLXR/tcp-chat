//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_PACKET_HPP
#define TCP_CHAT_PACKET_HPP

#include <string>
#include <vector>
#include "packettype.hpp"

class Packet {
public:
	explicit Packet() = default;
	explicit Packet(const char *buffer, int size);
	explicit Packet(const PacketType &packetType);
	Packet(const Packet &other);

	void append(const PacketType &packetType);
	void append(int value);
	void append(const std::wstring_view &string);
	void append(const char *data, int dataSize);

	inline const std::vector<char> &getBuffer() const { return buffer; }

private:
	std::vector<char> buffer;
};


#endif //TCP_CHAT_PACKET_HPP
