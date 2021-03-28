#include "Engine.h"

cEngine::cEngine() {
	
}

void cEngine::start(cOffsets* offsets_, vmem* mem_) {
	offsets = offsets_;
	mem = mem_;
	std::string a = "Counter-Strike: Global Offensive";
	strcpy(tWindowName, a.c_str());
	

	updateMisc();
	update();
	updateMeta();
}

void cEngine::update() {
	
	localPlayer = mem->read<uint32_t>(mem->client + offsets->dwLocalPlayer);

	shots = mem->read<uint32_t>(localPlayer + offsets->m_iShotsFired);
	health = mem->read<uint32_t>(localPlayer + offsets->m_iHealth);
	std::cout << health << "\n";
	int a = mem->read<int>(enginebase + 264/*offsets->dwClientState_State*/);
	isIngame = a == 6;
	team = mem->read<uint32_t>(localPlayer + 244/*offsets->m_iTeamNum*/);

	if (count %30 == 0) {
		updateMeta();
		updateMisc();
	}
}

void cEngine::updateMeta() {
	csInFront = !strcmp(tWindowName, GetActiveWindowTitle().c_str());
}

void cEngine::updateMisc() {
	enginebase = mem->read<DWORD>(mem->engine + offsets->dwClientState);
}
std::string cEngine::GetActiveWindowTitle() {
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}

