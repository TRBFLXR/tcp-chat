//
// Created by Igor on 2/9/2018.
//

#include "config.hpp"

Config gConfig;

bool Config::load(Config &config) {
	FILE *cfgFile = fopen("config", "rb");

	if (!cfgFile) {
		fclose(cfgFile);
		return false;
	}

	size_t size;
	fread(&size, sizeof(int), 1, cfgFile);
	config.name = std::wstring(size, L'\0');
	fread(&config.name[0], size, 1, cfgFile);

	fread(&size, sizeof(int), 1, cfgFile);
	config.ip = std::string(size, L'\0');
	fread(&config.ip[0], size, 1, cfgFile);

	fread(&config.port, sizeof(uint16_t), 1, cfgFile);

	fclose(cfgFile);

	gConfig = config;
	return true;
}

bool Config::save(const Config &config) {
	FILE *cfgFile = fopen("config", "wb");

	if (!cfgFile) {
		fclose(cfgFile);
		return false;
	}

	auto size = (int) config.name.size() * sizeof(wchar_t);
	fwrite(&size, sizeof(int), 1, cfgFile);
	fwrite(&config.name[0], size, 1, cfgFile);

	size = (int) config.ip.size();
	fwrite(&size, sizeof(int), 1, cfgFile);
	fwrite(&config.ip[0], size, 1, cfgFile);

	fwrite(&config.port, sizeof(uint16_t), 1, cfgFile);

	fclose(cfgFile);

	gConfig = config;
	return true;
}
