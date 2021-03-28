#ifndef BHOP_H
#define BHOP_H

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

class cBhop {
protected:


public:
	DWORD a;
	cBhop();

public:
	std::thread start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_);

private:
	cOffsets *offsets;
	vmem *mem;
	cConfig* cfg;
	cEngine* engine;

	void loop();
	void tick();

};
#endif