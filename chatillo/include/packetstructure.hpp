//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_PACKETSTRUCTURE_HPP
#define TCP_CHAT_PACKETSTRUCTURE_HPP

#include <vector>
#include <string>
#include <memory>

#include <packet.hpp>

namespace ps {

	struct Connect {
		explicit Connect(const std::wstring_view &name);
		std::shared_ptr<Packet> toPacket();

		std::wstring name;
	};

	struct Disconnect {
		explicit Disconnect(const std::wstring_view &name);
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

	struct UserList {
		explicit UserList(std::vector<std::wstring *> &users);
		std::shared_ptr<Packet> toPacket();

		std::vector<std::wstring *> users;
	};

	struct DuplicateName {
		explicit DuplicateName();
		std::shared_ptr<Packet> toPacket();
	};

}

#endif //TCP_CHAT_PACKETSTRUCTURE_HPP
