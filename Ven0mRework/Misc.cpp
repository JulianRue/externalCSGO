#include "Misc.h"

cMisc::cMisc() {

}

std::thread cMisc::start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_) {
	offsets = offsets_;
	mem = mem_;
	cfg = cfg_;
	engine = engine_;

	return std::thread([=] { loop(); });
}

void cMisc::loop() {
	for (;; Sleep(10)) {
		if (!engine->isIngame) continue;
		if (!engine->csInFront) continue;

		Trigger();
		/*
		if (engine->exit) {
			break;
		}
		*/
	}
}

void cMisc::Trigger() {
	if (GetAsyncKeyState(VK_MENU)) {
		DWORD local = mem->read<DWORD>(mem->client + offsets->dwLocalPlayer);
		int playernum = mem->read<DWORD>(local + offsets->m_iCrosshairId);

		if (playernum < 0 || playernum > 64) {
			return;
		}

		bool valid = false;

		DWORD entity = mem->read<DWORD>(mem->client + offsets->dwEntityList + ((playernum - 1) * offsets->oEntityLoopDistance));
		int team = mem->read<int>(entity + offsets->m_iTeamNum);
		if (team != 2 && team != 3) {
			return;
		}

		if (mem->read<DWORD>(local + offsets->m_iTeamNum) == team) {
			return;
		}

		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(50);
	}
}

void cMisc::Chams() {

}
/*
void cMisc::noFlash() {



	if (getNoFlashValue() < 100) {
		flashVal = true;
		if (mem->read<float>(localPlayer + offsets->m_flFlashMaxAlpha) != 1.0f && getNoFlashValue() == 0.0f) {
			mem->write<float>(localPlayer + offsets->m_flFlashMaxAlpha, 1.0f);
		}
		else if (read<float>(localPlayer + m_flFlashMaxAlpha) != getNoFlashValue() * 2.55) {
			write<float>(localPlayer + m_flFlashMaxAlpha, (float)getNoFlashValue() * 2.55);

		}
	}
	else if (!getNoFlashValue() && *flashFirst) {
		write<float>(localPlayer + m_flFlashMaxAlpha, 255.0f);
		*flashFirst = false;
	}
}

void noHands(bool * status) {


	if (getNoHands() && (read<DWORD>(localPlayer + m_nModelIndex) > 0)) {
		for (int i = 0; i < 10; i++) write<DWORD>(localPlayer + m_nModelIndex, 0);
		*status = true;
	}
	else if (!getNoHands() && *status) {
		*status = false;
		forceUpdate();
	}
}

void chams() {

	byte myteam[4] = { 0, 0 ,255, 255 };
	byte enemy[4] = { 255, 0 ,0, 255 };

	for (auto& player : players) {
		DWORD ent = player.entity;
		if (ent == localPlayer) continue;

		DWORD GlowIndex = player.GlowIndex;

		if (player.myTeam && getChamsTeam()) {
			if (getChamsTeamHealth()) {
				byte temp[4] = { 0, 255.f - (player.health / 100.f)*255.f , 255.f, 255.f };
				WriteProcessMemory(hWin, (LPVOID)(ent + m_clrRender), &temp, sizeof(temp), NULL);
			}
			else if (getChamsTeamOneColor()) {
				WriteProcessMemory(hWin, (LPVOID)(ent + m_clrRender), &myteam, sizeof(myteam), NULL);
			}
		}
		else if (!player.myTeam && getChamsEnemy()) {
			if (getChamsEnemyHealth()) {
				byte temp[4] = { 255.f - (player.health / 100.f)*255.f, (player.health / 100.f)*255.f , 0.f, 255.f };
				WriteProcessMemory(hWin, (LPVOID)(ent + m_clrRender), &temp, sizeof(temp), NULL);
			}
			else if (getChamsEnemyOneColor()) {
				WriteProcessMemory(hWin, (LPVOID)(ent + m_clrRender), &enemy, sizeof(enemy), NULL);
			}
		}
	}
}

void hitmarker(int* oldHits) {

	int newHits = read<DWORD>(localPlayer + m_totalHitsOnServer);
	if (*oldHits < newHits) {
		int current_weapon = cWeapons->getWeaponClass(myWeaponNr);
		if (current_weapon != 69) {
			if (getHitmarker(current_weapon)) {
				if (getHitmarkerSound() == 1)		PlaySoundA(hitsound_mario, NULL, SND_ASYNC | SND_MEMORY);
				else if (getHitmarkerSound() == 2) 	PlaySoundA(hitsound_cod, NULL, SND_ASYNC | SND_MEMORY);
				else if (getHitmarkerSound() == 3)	PlaySoundA(hitsound_roblox, NULL, SND_ASYNC | SND_MEMORY);
				else if (getHitmarkerSound() == 4) 	PlaySoundA(hitsound_skeet, NULL, SND_ASYNC | SND_MEMORY);
			}
		}
	}
	*oldHits = newHits;

}
*/