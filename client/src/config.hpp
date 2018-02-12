//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_CONFIG_HPP
#define TCP_CHAT_CONFIG_HPP

#include <string>
#include <cstdint>

struct Config {
	std::string ip;
	uint16_t port;

	std::wstring name;

	static constexpr uint16_t lineWidth = 63;
	static constexpr uint16_t tabSize = 3;

	static bool load(Config &config);
	static bool save(const Config &config);
};

extern Config gConfig;

#endif //TCP_CHAT_CONFIG_HPP