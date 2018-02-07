//
// Created by Igor on 2/7/2018.
//

#include <packetmanager.hpp>

void PacketManager::clear() {
	std::lock_guard<std::mutex> lock(mutex);
	packetQueue = std::queue<std::shared_ptr<Packet>> { };
}

bool PacketManager::hasPackets() {
	std::lock_guard<std::mutex> lock(mutex);
	return !packetQueue.empty();
}

void PacketManager::push(std::shared_ptr<Packet> packet) {
	std::lock_guard<std::mutex> lock(mutex);
	packetQueue.push(std::move(packet));
}

std::shared_ptr<Packet> PacketManager::pop() {
	std::lock_guard<std::mutex> lock(mutex);

	std::shared_ptr<Packet> p=packetQueue.front();
	packetQueue.pop();

	return p;
}
