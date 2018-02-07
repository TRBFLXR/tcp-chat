//
// Created by Igor on 2/7/2018.
//

#ifndef TCP_CHAT_PACKETMANAGER_HPP
#define TCP_CHAT_PACKETMANAGER_HPP

#include <queue>
#include <mutex>
#include <memory>

#include <packet.hpp>

class PacketManager {
public:
	void clear();
	bool hasPackets();

	void push(std::shared_ptr<Packet> packet);
	std::shared_ptr<Packet> pop();

private:
	std::queue<std::shared_ptr<Packet>> packetQueue;
	std::mutex mutex;
};


#endif //TCP_CHAT_PACKETMANAGER_HPP
