//
// Created by Igor on 2/6/2018.
//

#ifndef TCP_CHAT_PACKETTYPE_HPP
#define TCP_CHAT_PACKETTYPE_HPP

enum class PacketType {
	ChatMessage,
	RequestFile,
	FileBuffer,
	NextFileBuffer,
	EndOfFile
};


#endif //TCP_CHAT_PACKETTYPE_HPP
