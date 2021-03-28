#ifndef AIMBOT_H
#define AIMBOT_H

#define WIN32_LEAN_AND_MEAN
#include "Offsets.h"
#include "mem.h"
#include "Math.h"
#include "Engine.h"
#include "Config.h"

#include <windows.h>
#include <string>
#include <iostream>

class cAimbot {
protected:


public:
	cAimbot();

public:
	void start(cOffsets * offsets_, vmem* mem_, cConfig* cfg_, cEngine* engine_);
	float sens;

private:
	cOffsets * offsets;
	vmem *mem;
	cMath *math;
	cEngine* engine;
	cConfig* cfg;

	bool aim = false;
	float aimrandomX, aimrandomY;
	float Matrix[4][4];

	void tick();

	void worldToScreen(cMath::Vector * returner, cMath::Vector *worldLoc);
	void MoveMouse(float posX, float posY, float fov, float distance);
	float mouseMoveFOV(float X, float Y);
	float getFOV(int dist, int weapon);
	float Fov(cMath::Vector* Angle, cMath::VectorXY *PlayerAngle);
	void normalizeAngles(cMath::Vector* angles);
	void clampAngles(cMath::Vector* angles);
	void CalcLocalPos(cMath::Vector *returner);
	void getBonePos(cMath::Vector * returner, DWORD entity, int bone);
	void getBonePosW2S(cMath::Vector * returner, DWORD entity, int bone);
	void findClosestEntity(float * returnval, int * distance, bool boneScan, cMath::Vector *VecPosition, cMath::Vector *returner);
	int getBoneNum(int dist, int weapon, DWORD entity, cMath::VectorXY* currentAngles);
	void CalcAngle(cMath::Vector *returner, cMath::Vector *beginningVector, cMath::Vector *dstVector);
	cMath::Vector vPrevpunch = { 0,0,0 };
};
#endif