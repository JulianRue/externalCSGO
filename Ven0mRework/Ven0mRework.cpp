#include <iostream>
#include "mem.h"
#include "network.h"
#include "Offsets.h"
#include "Esp.h"
#include "Aimbot.h"
#include "Skinchanger.h"
#include "Misc.h"
#include "Bhop.h"
#include "Engine.h"

#include "Config.h"

cNetwork * network;
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <thread>

vmem mem;
cConfig cfg;


json scan() {
	int client = 0;
	int engine = 1;
	json j;

	PBYTE offset = (byte*)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF";

	std::string off1 = ("xxx????xx????xxxxxxxxx");
	char *offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwLocalPlayer"] = (DWORD)mem.GetOffset(client, offset, offset1, 3, true, true) + 4;
	
	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0";

	off1 = ("x????xxxxxxxxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwClientState"] = mem.GetOffset(engine, offset, offset1, 1, true, true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8";

	off1 = ("x????xxxxx????xx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwEntityList"] = mem.GetOffset(client, offset, offset1, 1, true, true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\x0F\x10\x05\x00\x00\x00\x00\x8D\x85\x00\x00\x00\x00\xB9";

	off1 = ("xxx????xx????x");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());
	
	j["dwViewMatrix"] = mem.GetOffset(client, offset, offset1, 3, true, true) + 176;

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE\x04";

	off1 = ("xx????xx????xxxxxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwForceAttack"] = mem.GetOffset(client, offset, offset1, 2, true, true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\x0F\x11\x05\x00\x00\x00\x00\x83\xC8\x01\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00";

	off1 = ("xxx????xxxxx????xxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());
	j["dwGlowObjectManager"] = mem.GetOffset(client, offset, offset1, 3, true, true) + 0;


	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02";

	off1 = ("xx????xxxxxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwForceJump"] = mem.GetOffset(client, offset, offset1, 2, true, true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05";

	off1 = ("xxxx????xxxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwClientState_ViewAngles"] = mem.GetOffset(engine, offset, offset1, 4, false, true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\xA1\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x80\xB8\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x0F\x10\x05";

	off1 = ("x????xxxx????xx?????xx????xxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwGameRulesProxy"] = mem.GetOffset(client, offset, offset1, 1, true,true);

	//-------------------------------------------------------------------------------------------------------------------------------

	offset = (byte*)"\xA1\x00\x00\x00\x00\x8B\x0C\xB0\x8B\x01\xFF\x50\x00\x46\x3B\x35\x00\x00\x00\x00\x7C\xEA\x8B\x0D";

	off1 = ("x????xxxxxxx?xxx????xxxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["dwRadarBase"] = mem.GetOffset(client, offset, offset1, 1, true, true);
	
	//----------

	offset = (byte*)"\x74\x07\x8B\xCB\xE8\x00\x00\x00\x00\x83\xC7\x10";
	off1 = ("xxxxx????xxx");
	offset1 = new char[off1.length() + 1];
	strcpy(offset1, off1.c_str());

	j["GlowPatch"] = mem.GetOffset(0, offset, offset1, 0, true, false);

	return j;
}


DWORD getHWID() {
	DWORD disk_serialINT;
	GetVolumeInformationA(NULL, NULL, NULL, &disk_serialINT, NULL, NULL, NULL, NULL);
	return disk_serialINT;
}

int main()
{

	mem.Process("csgo.exe",true,true);
	mem.client = mem.Module("client.dll");
	mem.engine = mem.Module("engine.dll");
	mem.engine_size = mem.GetModuleSize("engine.dll");
	mem.client_size = mem.GetModuleSize("client.dll");	
	
	json scans = scan();

	cOffsets offsets;
	offsets.init(NULL, scans);
	//offsets.init(server, scans);

	json j;
	json sub;

	j["key1"] = "key11";
	j["key2"] = "key22";
	sub["sub1"] = "sub11";
	sub["sub2"] = "sub22";
	sub["sub3"] = "sub33";
	j["sub"] = sub;

	
	std::cout << "Client.dll Size -> " << mem.client_size << "\n";
	std::cout << "-------------------------------\n";
	std::cout << "Client.dll Offset -> " << mem.client << "\n";
	std::cout << "Glow Patch Offset -> " << offsets.GlowPatch << "\n\n\n";

	//cfg.init(server["cfg"]);

	cEngine engine;
	engine.start(&offsets, &mem);
	
	cEsp esp;
	std::thread esp_thread = esp.start(&offsets, &mem, &cfg, &engine);

	//cSkinchanger skin;
	//std::thread skin_thread = skin.start(&offsets, &mem, &cfg, &engine);

	//cBhop bhop;
	//std::thread bhop_thread = bhop.start(&offsets, &mem, &cfg, &engine);

	//cMisc misc;
	//std::thread misc_thread = misc.start(&offsets, &mem, &cfg, &engine);


	std::cout << "waiting for esp...\n";
	esp_thread.join();
	std::cout << "Cheat closing!\n";

	cAimbot aa;
	//aa.start(&offsets, &mem, &cfg, &engine);

	

	exit(1);
}