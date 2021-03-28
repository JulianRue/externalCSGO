#include "Aimbot.h"

cAimbot::cAimbot() {

}

void cAimbot::start(cOffsets* offsets_, vmem* mem_, cConfig* cfg_, cEngine* engine_) {
	offsets = offsets_;
	mem = mem_;
	cfg = cfg_;
	engine = engine_;
	auto sensAdress = std::int32_t(mem->client + offsets->dwSensitivityPtr); //SensitivityPtr
	auto sensPtr = sensAdress + 44;							//Sensitivity
	auto cvar_xor = mem->read<std::int32_t>(sensPtr) ^ sensAdress;
	sens = *reinterpret_cast<std::float_t*>(&cvar_xor);
	printf("sens: %ff, xored: %i\n", sens, cvar_xor);

	while (true) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			tick();
			//std::cout << "Tick.\n";
		}
		Sleep(30);		
	}
}

void MouseMove(double x, double y)
{
	double fx = x;// *(65535.0f / 960);
	double fy = y;// *(65535.0f / 540);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
}




void cAimbot::getBonePosW2S(cMath::Vector * returner, DWORD entity, int bone) {
	cMath::Vector value;
	cMath::Vector error;
	DWORD bonematrix = mem->read<DWORD>(entity + offsets->m_dwBoneMatrix);

	if (bonematrix == NULL) {
		*returner = { 0,0,0 };
	}

	value.x = mem->read<float>(bonematrix + 0x30 * bone + 0x0C);
	value.y = mem->read<float>(bonematrix + 0x30 * bone + 0x1C);
	value.z = mem->read<float>(bonematrix + 0x30 * bone + 0x2C);


	worldToScreen(returner, &value);
}

void cAimbot::getBonePos(cMath::Vector * returner, DWORD entity, int bone) {
	cMath::Vector value;
	cMath::Vector error;
	DWORD bonematrix = mem->read<DWORD>(entity + offsets->m_dwBoneMatrix);

	if (bonematrix == NULL) {
		*returner = { 0,0,0 };
	}

	value.x = mem->read<float>(bonematrix + 0x30 * bone + 0x0C);
	value.y = mem->read<float>(bonematrix + 0x30 * bone + 0x1C);
	value.z = mem->read<float>(bonematrix + 0x30 * bone + 0x2C);

	*returner = value;
}

void cAimbot::CalcLocalPos(cMath::Vector *returner) {
	cMath::Vector Origin = mem->read<cMath::Vector>(engine->localPlayer + offsets->m_vecOrigin);
	std::cout << "Origin -> X: " << Origin.x << " Y: " << Origin.y << " Z: " << Origin.z << "\n";
	cMath::Vector ViewVector = mem->read<cMath::Vector>(engine->localPlayer + offsets->m_vecViewOffset);
	cMath::Vector temp = { Origin.x + ViewVector.x, Origin.y + ViewVector.y, Origin.z + ViewVector.z };
	*returner = temp;
}

void cAimbot::CalcAngle(cMath::Vector *returner, cMath::Vector *beginningVector, cMath::Vector *dstVector) {
	cMath::Vector temp = { (beginningVector->x - dstVector->x), (beginningVector->y - dstVector->y), (beginningVector->z - dstVector->z) };
	double pytagoras = sqrt(pow(temp.x, 2) + pow(temp.y, 2)); //satz des Pytagoras a^2 + b^2 = c^2
	cMath::Vector NewAngles = { 0,0,0 };
	
	NewAngles.x = (float)(atan(temp.z / pytagoras) * 57.295779513082f); //Vertikal 
	NewAngles.y = (float)(atan(temp.y / temp.x) * 57.295779513082f); //Horizontal
	NewAngles.z = 0.0f;
	
	if (temp.x >= 0.0)	NewAngles.y += 180.0f;
	
	cMath::Vector punch = mem->read<cMath::Vector>(engine->localPlayer +  offsets->m_aimPunchAngle);
	NewAngles.x -= (punch.x * 2);
	NewAngles.y -= (punch.y * 2);

	if (false) { //humanized
		if (aim) {
			aimrandomX = math->RandomFloat(-1 * /*config min*/10, /*config maxn*/ 10) / 10.0f;
			aimrandomY = math->RandomFloat(-1 * /*config min*/10, /*config maxn*/ 10) / 10.0f;
			NewAngles.x += aimrandomX;
			NewAngles.y += aimrandomY;

			aim = !aim;
		}
		else {

			if (aimrandomX > 0) {
				NewAngles.x -= aimrandomX;
			}
			else {
				NewAngles.x += sqrt(pow(aimrandomX, 2));
			}

			if (aimrandomY > 0) {
				NewAngles.y -= aimrandomY;
			}
			else {
				NewAngles.y += sqrt(pow(aimrandomY, 2));
			}

			aim = !aim;
		}
	}

	*returner = NewAngles;
}

void cAimbot::normalizeAngles(cMath::Vector* angles) {
	while (angles->x > 89.f)
		angles->x -= 180.f;

	while (angles->x < -89.f)
		angles->x += 180.f;

	while (angles->y > 180.f)
		angles->y -= 360.f;

	while (angles->y < -180.f)
		angles->y += 360.f;
}

void cAimbot::clampAngles(cMath::Vector* angles) {
	if (angles->x > 89.0)
		angles->x = 89.0;

	if (angles->x < -89.0)
		angles->x = -89.0;

	if (angles->y > 180.0)
		angles->y = 180.0;

	if (angles->y < -180.0)
		angles->y = -180.0;

	angles->z = 0;
}

float cAimbot::Fov(cMath::Vector* Angle, cMath::VectorXY *PlayerAngle) {
	float fov = sqrt(pow(Angle->x - PlayerAngle->x, 2) + pow(Angle->y - PlayerAngle->y, 2));
	if (fov > 180)
	{
		return abs(360.f - fov);
	}
	return fov;
}

float cAimbot::getFOV(int dist, int weapon) {
	float fov = 0;
	//int shots = totalShots;

	if (weapon == 666) return 0;

	/*
	int dynshots = getDynFovShots(weapon);
	if (getDynFov(weapon)) {
		if (dynshots > 0) {
			fov += (getDynFovVal(weapon) * (shots / dynshots));
		}
	}
	*/

	if (dist < 400) {
		return fov + 30; // getFov_close(weapon);
	}

	else if (dist < 850) {
		return fov + 20; // getFov_mid(weapon);
	}
	else {
		return fov + 10; // getFov_far(weapon);
	}
}

int cAimbot::getBoneNum(int dist, int weapon, DWORD entity, cMath::VectorXY *currentAngles) {

	cMath::Vector *LocalHeadPos = new cMath::Vector;
	*LocalHeadPos = { 0,0,0 };

	CalcLocalPos(LocalHeadPos);
	
	int boneArr[4] = { 8,7,6,4 };
	float tempFOV = 999;
	int returner = 0;

	cMath::Vector *EnemyBonePos;
	cMath::Vector *Angle;

	if (dist < 400) {
		if (false) { // close closest bone
			for (int i = 0; i < 4; i++) {
				getBonePos(EnemyBonePos, entity, boneArr[i]);
				if (EnemyBonePos->x == NULL || EnemyBonePos->y == NULL || EnemyBonePos->z == NULL) continue;
		
				CalcAngle(Angle, LocalHeadPos, EnemyBonePos);

				normalizeAngles(Angle);
				clampAngles(Angle);

				float FOV = Fov(Angle, currentAngles);
				int MAXFOV = getFOV(math->getDistance(LocalHeadPos, EnemyBonePos), weapon);
				if (FOV > MAXFOV) continue;

				if (FOV < tempFOV) {
					tempFOV = FOV;
					returner = boneArr[i];
				}
			}

			if (returner)	return returner;
			else return 6;
		}
		else {
			return 30; //return getBoneClose(weapon);
		}

	}
	else if (dist < 850) {
		if (false) { // mid closest bone
			for (int i = 0; i < 4; i++) {
				getBonePos(EnemyBonePos, entity, boneArr[i]);
				if (EnemyBonePos->x == NULL || EnemyBonePos->y == NULL || EnemyBonePos->z == NULL) continue;

				CalcAngle(Angle, LocalHeadPos, EnemyBonePos);

				normalizeAngles(Angle);
				clampAngles(Angle);

				float FOV = Fov(Angle, currentAngles);
				int MAXFOV = getFOV(math->getDistance(LocalHeadPos, EnemyBonePos), weapon);
				if (FOV > MAXFOV) continue;

				if (FOV < tempFOV) {
					tempFOV = FOV;
					returner = boneArr[i];
				}
			}

			if (returner)	return returner;
			else return 6;
		}
		else {
			return 20; //return getBoneMid(weapon);
		}
	}
	else {
		if (false) { // close closest bone
			for (int i = 0; i < 4; i++) {
				getBonePos(EnemyBonePos, entity, boneArr[i]);
				if (EnemyBonePos->x == NULL || EnemyBonePos->y == NULL || EnemyBonePos->z == NULL) continue;

				CalcAngle(Angle, LocalHeadPos, EnemyBonePos);

				normalizeAngles(Angle);
				clampAngles(Angle);

				float FOV = Fov(Angle, currentAngles);
				int MAXFOV = getFOV(math->getDistance(LocalHeadPos, EnemyBonePos), weapon);
				if (FOV > MAXFOV) continue;

				if (FOV < tempFOV) {
					tempFOV = FOV;
					returner = boneArr[i];
				}
			}

			if (returner)	return returner;
			else return 6;
		}
		else {
			return 30; //return getBoneClose(weapon);
		}
	}
}

float cAimbot::mouseMoveFOV(float X, float Y) {
	float ydist = (Y - mem->height / 2);

	float xdist = (X - mem->width/ 2);

	float Hypotenuse = sqrt(pow(ydist, 2) + pow(xdist, 2));
	return Hypotenuse;
}


void cAimbot::worldToScreen(cMath::Vector * returner, cMath::Vector *worldLoc) {

	cMath::Vector value;

	value.x = Matrix[0][0] * worldLoc->x + Matrix[0][1] * worldLoc->y + Matrix[0][2] * worldLoc->z + Matrix[0][3];
	value.y = Matrix[1][0] * worldLoc->x + Matrix[1][1] * worldLoc->y + Matrix[1][2] * worldLoc->z + Matrix[1][3];
	value.z = Matrix[3][0] * worldLoc->x + Matrix[3][1] * worldLoc->y + Matrix[3][2] * worldLoc->z + Matrix[3][3];


	if (value.z > 0.1f) {
		value.x = value.x * (1.0f / value.z);
		value.y = value.y * (1.0f / value.z);
		float x = mem->width / 2.0f;
		float y = mem->height / 2.0f;
		x += 0.5f * value.x * mem->width + 0.5f;
		y -= 0.5f * value.y * mem->height + 0.5f;
		value.x = x + mem->tSize.left;
		value.y = y + mem->tSize.top;

		*returner = value;
	}
	else {
		*returner = { 0,0,0 };
	}


}


void cAimbot::findClosestEntity(float * returnval, int * distance, bool boneScan, cMath::Vector *VecPosition, cMath::Vector *returner) {
	
	float tempFOV = 9999;
	*returner = { 0.0f,0.0f,0.0f };
	float fov = 0;
	int tempDist = 0;
	const int boneArr[4] = { 8,7,6,4 };
	cMath::Vector temp;

	cMath::Vector localPos;

	CalcLocalPos(&localPos);
	
	ReadProcessMemory(mem->hProcess, (LPVOID)(mem->client + offsets->dwViewMatrix), &Matrix, sizeof(Matrix), NULL);
	
	cMath::VectorXY currentAngles =	mem->read<cMath::VectorXY>(mem->read<DWORD>(mem->engine + offsets->dwClientState) + offsets->dwClientState_ViewAngles);

	//engine
	int myWeapon = 0;
	
	for (int i = 0; i < 64; i++) {

		DWORD entity = mem->read<DWORD>(mem->client + offsets->dwEntityList + i * offsets->oEntityLoopDistance);
		if (entity == NULL) continue;

		int health = mem->read<int>(entity + offsets->m_iHealth);
		if (health < 1) continue;

		if (mem->read<bool>(entity + offsets->m_bDormant)) continue;

		int team = mem->read<int>(entity + offsets->m_iTeamNum);
		if (team == engine->team || (team != 2 && team != 3)) continue;

		//spotted check

		cMath::Vector pos_;
		getBonePos(&pos_, entity, 8);
		std::cout << "----------------------------\n";
		std::cout << "Local -> X: " << localPos.x << " Y: " << localPos.y << " Z: " << localPos.z << "\n";
		std::cout << "Player -> X: " << pos_.x << " Y: " << pos_.y << " Z: " << pos_.z << "\n";
		float distance_ = math->getDistance(&pos_, &localPos);

		std::cout << "Distance: " << distance_ << "\n";
		int bone = getBoneNum(distance_, myWeapon, entity, &currentAngles);

		if (bone != 8) {
			getBonePos(&pos_, entity, bone);
		}
		
		
		cMath::Vector pos;
		cMath::Vector value;	
		worldToScreen(&pos, &pos_);

		std::cout << "Player -> X: " << pos.x << " Y: " << pos.y << "\n";
		fov = mouseMoveFOV(pos.x, pos.y);

		int MAXFOV = getFOV(distance_, myWeapon);

		MAXFOV *= 4;


		std::cout << "MAXFOV = " << MAXFOV << "\n";
		std::cout << "fov = " << fov << "\n";

		if (fov > MAXFOV) continue;


		if (fov < tempFOV) {
			tempDist = distance_;
			tempFOV = fov;
			temp = pos;
			*returnval = tempFOV;
			worldToScreen(returner, &pos_);
			*distance = tempDist;
			*VecPosition = temp;
			std::cout << "Closest at X:" << returner->x << " Y:" << returner->y << " Z:" << returner->z << "\n";
		}
		
	}

}

void cAimbot::MoveMouse(float posX, float posY, float fov, float distance) {
	float AimSpeed = 0;
	float enemyX, enemyY = 0;
	float random = math->RandomFloat(-100, 100);
	if (random != 0) random /= 200.0f;

	float AimSpeed_ = math->RandomInt(1, 4);


	//[JUNK]


	if (distance < 400) {
		AimSpeed = 50.f/*auf config*/ / 10.f;
		if (AimSpeed > 10) AimSpeed = 10;
		else if (AimSpeed < 1) AimSpeed = 1.5;
	}
	else if (distance < 850) {
		AimSpeed = 50.f/*auf config*/ / 10.f;
		if (AimSpeed > 10) AimSpeed = 10;
		else if (AimSpeed < 1) AimSpeed = 1.5;
	}
	else {
		AimSpeed = 50.f/*auf config*/ / 10.f;
		if (AimSpeed > 10) AimSpeed = 10;
		else if (AimSpeed < 1) AimSpeed = 1.5;
	}

	if (posX != 0) {
		if (posX > mem->width / 2) {
			enemyX = (-((mem->width / 2) - posX)) / AimSpeed;
			if ((enemyX + (mem->width / 2)) > mem->width) enemyX = 0;
		}
		if (posX < mem->width / 2) {
			enemyX = (posX - mem->width / 2) / AimSpeed;
			if ((enemyX + (mem->width / 2)) < 0) enemyX = 0;
		}
	}
	if (posY != 0) {
		if (posY > (mem->height / 2)) {
			enemyY = (-((mem->height / 2) - posY)) / AimSpeed;
			if ((enemyY + (mem->height / 2)) > mem->height) enemyY = 0;
		}
		if (posY < mem->height / 2) {
			enemyY = (posY - mem->height / 2) / AimSpeed;
			if ((enemyY + (mem->height / 2)) < 0) enemyY = 0;
		}
	}

	if (fov > 25){
		enemyX /= AimSpeed;
		enemyY /= AimSpeed;
		if (1 != 1) {
			if (fabs(enemyX) < 1) {
				if (enemyX > 0) enemyX = (fov / 10);
				if (enemyX < 0) enemyX = -(fov / 10);
			}
			if (fabs(enemyY) < 1) {
				if (enemyY > 0) enemyY = (fov / 10);
				if (enemyY < 0) enemyY = -(fov / 10);
			}
		}
		else {
			if (fabs(enemyX) < 1) {
				if (enemyX > 0) enemyX = 1;
				if (enemyX < 0) enemyX = -1;
			}
			if (fabs(enemyY) < 1) {
				if (enemyY > 0) enemyY = 1;
				if (enemyY < 0) enemyY = -1;
			}
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, enemyX, enemyY, NULL, NULL);
}


void cAimbot::tick() {
	
	cMath::Vector pos;
	float fov;
	int distance;
	
	cMath::Vector Angle;
	findClosestEntity(&fov, &distance, false, &pos, &Angle);

	if (Angle.x == 0.0f || Angle.y == 0.0f) return;
	if (fov > 10) {
		MoveMouse(Angle.x, Angle.y, fov, distance);
	}
	else {
		while (GetAsyncKeyState(VK_LBUTTON))Sleep(5);
	}
	
		/*
		totalShots = read<DWORD>(localPlayer + m_iShotsFired);

		current_weapon = cWeapons->getWeaponClass(myWeaponNr);

		if (current_weapon == 69) continue;

		if (getRcs(current_weapon) < 1) {
			Sleep(50);
			continue;
		}

		if (totalShots < 1) {
			continue;
		}

		while (GetAsyncKeyState(VK_LBUTTON) || read<DWORD>(dw_Client + dwForceAttack) == 5) {
			Vector VecPunch = read<Vector>(localPlayer + m_aimPunchAngle);
			Vector CurrentAngles = read<Vector>(engineBase + dwClientState_ViewAngles);
			Vector diff = CurrentAngles;

			VecPunch.x *= 0.02*getRcs(current_weapon);
			VecPunch.y *= 0.02*getRcs(current_weapon);

			CurrentAngles.x = CurrentAngles.x - VecPunch.x + oldPunch.x;
			CurrentAngles.y = CurrentAngles.y - VecPunch.y + oldPunch.y;

			normalizeAngles(CurrentAngles);
			clampAngles(CurrentAngles);

			write<Vector>((engineBase + dwClientState_ViewAngles), CurrentAngles);

			oldPunch.x = VecPunch.x;
			oldPunch.y = VecPunch.y;

			Sleep(8);
		}
		oldPunch.x = 0.0f;
		oldPunch.y = 0.0f; // = read<Vector>(localPlayer + m_aimPunchAngle);
		*/
	
		

}