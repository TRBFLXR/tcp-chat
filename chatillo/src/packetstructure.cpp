//
// Created by Igor on 2/7/2018.
//

#include <packetstructure.hpp>

///Connect
ps::Connect::Connect(const std::wstring_view &name) : name(name) { }

std::shared_ptr<Packet> ps::Connect::toPacket() {
	std::shared_ptr<Packet> p = std::make_shared<Packet>();

	p->append(PacketType::Connect);
	p->append((int) name.size() * sizeof(wchar_t));
	p->append(name);

	return p;
}

///Disconnect
ps::Disconnect::Disconnect(const std::wstring_view &name) : name(name) { }

std::shared_ptr<Packet> ps::Disconnect::toPacket() {
	std::shared_ptr<Packet> p = std::make_shared<Packet>();

	p->append(PacketType::Disconnect);
	p->append((int) name.size() * sizeof(wchar_t));
	p->append(name);

	return p;
}

///ChatMessage
ps::ChatMessage::ChatMessage(const std::wstring_view &message) : message(message) { }

std::shared_ptr<Packet> ps::ChatMessage::toPacket() {
	std::shared_ptr<Packet> p = std::make_shared<Packet>();

	p->append(PacketType::ChatMessage);
	p->append((int) message.size() * sizeof(wchar_t));
	p->append(message);

	return p;
}

///ServerChatMessage
ps::ServerChatMessage::ServerChatMessage(const std::wstring_view &message, const std::wstring_view &sender) :
		message(message), sender(sender) { }

std::shared_ptr<Packet> ps::ServerChatMessage::toPacket() {
	std::shared_ptr<Packet> p = std::make_shared<Packet>();

	p->append(PacketType::ServerChatMessage);
	p->append((int) message.size() * sizeof(wchar_t));
	p->append(message);
	p->append((int) sender.size() * sizeof(wchar_t));
	p->append(sender);

	return p;
}