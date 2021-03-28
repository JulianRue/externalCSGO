#ifndef ENGINE_H
#define ENGINE_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>

#include "Offsets.h"
#include "mem.h"
#include "Classid.h"

class cEngine {
protected:


public:

	uint32_t activeWeapon;
	short activeWeaponID;

	int shots;
	uint32_t localPlayer;
	int health;
	bool isIngame;
	uint32_t enginebase;
	bool csInFront;
	bool exit = false;
	int team;

public:
	
	void start(cOffsets *offsets_, vmem *mem_);
	void update();
	
	std::string GetActiveWindowTitle();
	cEngine();
	
private:
	vmem* mem;
	cOffsets* offsets;

	int count = 0;
	void updateMeta();
	void updateMisc();

	char tWindowName[256];
};
#endif