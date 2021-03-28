#ifndef SKINCHANGER_H
#define SKINCHANGER_H

#define WIN32_LEAN_AND_MEAN
#include "Offsets.h"
#include "mem.h"
#include "Classid.h"
#include "Engine.h"
#include "Config.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <thread>

class cSkinchanger {
protected:


public:
	DWORD a;
	cSkinchanger();

public:
	std::thread start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_);
	void loop();
	
private:
	cOffsets *offsets;
	vmem *mem;
	cEngine* engine;
	cConfig* cfg;

	void skinsX();
	void knife();
	std::thread loop1();
	int skin_();
	
	#define precache_bayonet_ct 89 // = v_knife_bayonet.mdl - v_knife_default_ct.mdl
	#define precache_bayonet_t 65 // = v_knife_bayonet.mdl - v_knife_default_t.mdl

	

	enum knifeDefinitionIndex               // id
	{
		WEAPON_KNIFE = 42,
		WEAPON_KNIFE_T = 59,
		WEAPON_KNIFE_BAYONET = 500,         // 0
		WEAPON_KNIFE_CSS = 503,				// 1
		WEAPON_KNIFE_FLIP = 505,            // 2
		WEAPON_KNIFE_GUT = 506,             // 3
		WEAPON_KNIFE_KARAMBIT = 507,        // 4
		WEAPON_KNIFE_M9_BAYONET = 508,      // 5
		WEAPON_KNIFE_TACTICAL = 509,        // 6
		WEAPON_KNIFE_FALCHION = 512,        // 7
		WEAPON_KNIFE_SURVIVAL_BOWIE = 514,  // 8
		WEAPON_KNIFE_BUTTERFLY = 515,       // 9
		WEAPON_KNIFE_PUSH = 516,            // 10
		WEAPON_KNIFE_URSUS = 519,           // 11
		WEAPON_KNIFE_GYPSY_JACKKNIFE = 520, // 12
		WEAPON_KNIFE_STILETTO = 522,        // 13
		WEAPON_KNIFE_WIDOWMAKER = 523       // 14
	};

	short knifeIDs[15] = { WEAPON_KNIFE_BAYONET,
		WEAPON_KNIFE_CSS,
		WEAPON_KNIFE_FLIP,
		WEAPON_KNIFE_GUT,
		WEAPON_KNIFE_KARAMBIT,
		WEAPON_KNIFE_M9_BAYONET,
		WEAPON_KNIFE_TACTICAL,
		WEAPON_KNIFE_FALCHION,
		WEAPON_KNIFE_SURVIVAL_BOWIE,
		WEAPON_KNIFE_BUTTERFLY,
		WEAPON_KNIFE_PUSH,
		WEAPON_KNIFE_URSUS,
		WEAPON_KNIFE_GYPSY_JACKKNIFE,
		WEAPON_KNIFE_STILETTO,
		WEAPON_KNIFE_WIDOWMAKER
		
	};

};

#endif