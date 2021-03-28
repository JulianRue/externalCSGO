#include "Config.h"

cConfig::cConfig() {

}

void cConfig::init(json config_) {
	config = config_;

	try {
		std::cout << "Config -> " << config["esp"]["enemy_health"].get<bool>() << "\n";
		esp_enemy_health = config["esp"]["enemy_health"].get<bool>();
		esp_team_health = config["esp"]["team_health"].get<bool>();
	}
	catch (...) {
		std::cout << "error0\n";
		system("pause");
		exit(0);
	}

	try {
		knife_Float = config["skinchanger"]["knife"]["float"].get<float>();
		knife_ID = config["skinchanger"]["knife"]["id"].get<int>();
		std::string asd = config["skinchanger"]["knife"]["name"].get<std::string>();
		//strcpy(knife_Name, asd.c_str());
		knife_Seed = config["skinchanger"]["knife"]["seed"].get<int>();
		knife_Skin = config["skinchanger"]["knife"]["skin"].get<int>();
		knife_Stattrack = config["skinchanger"]["knife"]["stattrack"].get<int>();
	}
	catch (...) {
		std::cout << "error1\n";
		system("pause");
		exit(0);
	}

	std::cout << "\"" << config["name"].get<std::string>() << "\" loaded.\nConfig ID: " << config["id"].get<int>() << "\n-----------------------\n";
}

int cConfig::getSkin(short id) {
	std::string a = std::to_string(id);
	try {
		return config["skinchanger"]["skins"][a]["paintkit"].get<int>();
	}
	catch (...) {
		return -1;
	}
}

int cConfig::getSeed(short id) {
	std::string a = std::to_string(id);
	try {
		return config["skinchanger"]["seeds"][a]["seed"].get<int>();
	}
	catch (...) {
		return -1;
	}
}

int cConfig::getStattrack(short id) {
	std::string a = std::to_string(id);
	try {
		return config["skinchanger"]["stattrack"][a]["stattrack"].get<int>();
	}
	catch (...) {
		return -1;
	}
}

char* cConfig::getName(short id) {
	char* ret;
	std::string b = "";
	std::string a = std::to_string(id);
	try {
		strcpy(ret, (config["skinchanger"]["name"][a]["name"].get<std::string>()).c_str());
	}
	catch (...) {
		strcpy(ret, b.c_str());
	}
	return ret;
}

float cConfig::getFloat(short id) {
	std::string a = "" + std::to_string(id);
	try {
		return config["skinchanger"]["float"][a]["float"].get<float>();
	}
	catch (...) {
		return -1;
	}
}