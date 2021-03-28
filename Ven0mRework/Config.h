#ifndef CONFIG_H
#define CONFIG_H

#define WIN32_LEAN_AND_MEAN
#include "Offsets.h"
#include "mem.h"

#include <windows.h>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

class cConfig {
protected:

public:
	cConfig();
	void init(json config);

	bool esp_enemy_health = false;
	bool esp_team_health = false;

	int knife_ID;
	int knife_Skin;
	int knife_Seed;
	int knife_Stattrack;
	float knife_Float;
	char* knife_Name;

	

public:
	int getSkin(short id);
	int getSeed(short id);
	int	getStattrack(short id);
	char*	getName(short id);
	float	getFloat(short id);
private:
	json config;

	
};

#endif