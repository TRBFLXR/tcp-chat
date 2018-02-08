//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_PACKETSTRUCTURE_HPP
#define TCP_CHAT_PACKETSTRUCTURE_HPP

#include <string>
#include <memory>

#include <packet.hpp>

namespace ps {

	struct ChatMessage {
		explicit ChatMessage(const std::wstring_view &message);

		std::shared_ptr<Packet> toPacket();

		std::wstring sender;
		std::wstring message;
	};

}

#endif //TCP_CHAT_PACKETSTRUCTURE_HPP
