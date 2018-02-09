//
// Created by Igor on 2/9/2018.
//

#include "config.hpp"

Config gConfig{ };

bool Config::load(Config &config) {
	config.name = L"name";
	config.ip = "109.87.123.75";
	config.port = 1111;

	gConfig = config;

	return true;
}

void Config::save(const Config &config) {

}
