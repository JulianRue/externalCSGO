#include "Bhop.h"

cBhop::cBhop() {

}

std::thread cBhop::start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_) {
	offsets = offsets_;
	mem = mem_;
	cfg = cfg_;
	engine = engine_;

	return std::thread([=] { loop(); });
}

void cBhop::loop() {
	int count = 0;
	int random = 0;
	DWORD flag;

	for (;; Sleep(2)) {

		if (!engine->csInFront || !engine->isIngame) {
			Sleep(100);
			continue;
		}

		if (engine->health < 1 || !GetAsyncKeyState(VK_SPACE)) {
			return;
		}
		
		count = 0;

		while (GetAsyncKeyState(VK_SPACE)) {

			
			INPUT space = { 0 };
			space.type = INPUT_KEYBOARD;
			space.ki.wVk = VK_SPACE;
			SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
			space.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &space, sizeof(INPUT)); // Send KeyUp
			
			Sleep(10);
			
			flag = mem->read<DWORD>(engine->localPlayer + offsets->m_fFlags);

			//while ((flag != FL_ON_GROUND && flag != FL_ON_GROUND_CROUCHED) && GetAsyncKeyState(VK_SPACE)) {
				//flag = mem->read<DWORD>(local + offsets->m_fFlags);
			//}

			//mem->write<DWORD>((mem->client + offsets->dwForceJump), 5);
			//Sleep(10);
			//mem->write<DWORD>((mem->client + offsets->dwForceJump), 4);

			/*
			if (getBhopSound() > 0) {
				PlaySoundA(jump_mario2, NULL, SND_ASYNC | SND_MEMORY);
			}
			else {
				Sleep(50);
			}
			*/

			
		}
	}
}
