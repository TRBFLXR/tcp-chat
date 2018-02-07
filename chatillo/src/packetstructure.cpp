//
// Created by Igor on 2/7/2018.
//

#include <packetstructure.hpp>

ps::ChatMessage::ChatMessage(const std::wstring_view &message) : message(message) { }

std::shared_ptr<Packet> ps::ChatMessage::toPacket() {
	std::shared_ptr<Packet> p = std::make_shared<Packet>();

	p->append(PacketType::ChatMessage);
	p->append((int) message.size() * sizeof(wchar_t));
	p->append(message);

	return p;
}

