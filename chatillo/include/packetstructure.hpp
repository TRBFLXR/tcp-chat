//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_PACKETSTRUCTURE_HPP
#define TCP_CHAT_PACKETSTRUCTURE_HPP

#include <string>
#include <memory>

#include <packet.hpp>

namespace ps {

	struct Register {
		explicit Register(const std::wstring_view &name);
		std::shared_ptr<Packet> toPacket();

		std::wstring name;
	};

	struct ChatMessage {
		explicit ChatMessage(const std::wstring_view &message);
		std::shared_ptr<Packet> toPacket();

		std::wstring message;
	};

	struct ServerChatMessage {
		explicit ServerChatMessage(const std::wstring_view &message, const std::wstring_view &sender);
		std::shared_ptr<Packet> toPacket();

		std::wstring sender;
		std::wstring message;
	};

}

#endif //TCP_CHAT_PACKETSTRUCTURE_HPP
