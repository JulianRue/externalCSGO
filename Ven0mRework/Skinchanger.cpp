#include "Skinchanger.h"

DWORD modelIndex = 0;
DWORD cachedPlayer = 0;
bool wait = false;
long lastTimer = 0;
long lastKnife = 0;
DWORD knifeID;
short itemDef;
DWORD paintKit;

cSkinchanger::cSkinchanger() {

}

void cSkinchanger::knife() {


	std::cout << "started knife\n";
	int knifeIDOffset = knifeID < 10 ? 0 : 1; /* precache offset id by 1 for new knives */
	Sleep(100);

	while (true) {

		if (wait) {
			Sleep(1);
			continue;
		}


		uint32_t WeaponEntity = (mem->read<uint32_t>(engine->localPlayer + offsets->m_hActiveWeapon) & 0xFFF) - 1;
		engine->activeWeapon = mem->read<uint32_t>(mem->client + offsets->dwEntityList + (WeaponEntity * offsets->oEntityLoopDistance));

		engine->activeWeaponID = mem->read<short>(engine->activeWeapon + offsets->m_iItemDefinitionIndex);

		/* viewmodel id of the weapon in our hands (default ct knife should usually be around 300) */
		int weaponViewModelID = mem->read<int>(engine->activeWeapon + offsets->m_iViewModelIndex);

		/* calculate the correct modelindex using the index of default knives and the precache list */
		if (engine->activeWeaponID == WEAPON_KNIFE && weaponViewModelID > 0)
		{
			modelIndex = weaponViewModelID + precache_bayonet_ct + 3 * knifeID + knifeIDOffset + 3;
		}
		else if (engine->activeWeaponID == WEAPON_KNIFE_T && weaponViewModelID > 0)
		{
			modelIndex = weaponViewModelID + precache_bayonet_t + 3 * knifeID + knifeIDOffset + 3;
		}
		else if (engine->activeWeaponID != itemDef || modelIndex == 0) {
			lastKnife = time(NULL);
			Sleep(1);
			continue;
		}



		/* handle to viewmodel entity we will use to change the knife viewmodel index */
		DWORD knifeViewModel = mem->read<DWORD>(engine->localPlayer + offsets->m_hViewModel) & 0xfff;
		knifeViewModel = mem->read<DWORD>(mem->client + offsets->dwEntityList + (knifeViewModel - 1) * 0x10);
		if (knifeViewModel == 0) { continue; }

		/* change our current viewmodel but only if localplayer is holding a knife in hands */
		if (time(NULL) - lastKnife < 4) {
			mem->write<DWORD>(knifeViewModel + offsets->m_nModelIndex, modelIndex);
		}
		else {
			Sleep(5);
			continue;
		}
	}
}

void cSkinchanger::skinsX()
{
	const int itemIDHigh = -1;
	const int entityQuality = 3;
	int stattrack, seed;
	float _float;
	char name[20];

	while (!GetAsyncKeyState(VK_F9))
	{
		if (GetAsyncKeyState(VK_CONTROL)) {
			lastTimer = time(NULL);
			Sleep(50);
			mem->write<int>(engine->enginebase + offsets->ForceUpdate, -1);
		}


		if (!engine->isIngame) {
			Sleep(1);
			wait = true;
			continue;
		}

		if (engine->localPlayer == 0) /* localplayer is not connected to any server (unreliable method) */
		{
			wait = true;
			modelIndex = 0;
			Sleep(1000);
			continue;
		}
		else if (engine->localPlayer != cachedPlayer) /* localplayer changed by server switch / demo record */
		{
			modelIndex = 0;
			cachedPlayer = engine->localPlayer;
		}

		wait = false;

		if (GetAsyncKeyState(0x42)) { // B Pressed
			std::cout << "Timer Resetted\n";
			lastTimer = time(NULL);
		}

		if (time(NULL) - lastTimer > 10) {
			Sleep(2);
			continue;
		}

		for (int i = 0; i < 8; i++) {

			/* handle to weapon entity in the current slot */
			DWORD currentWeapon = mem->read<DWORD>(engine->localPlayer + offsets->m_hMyWeapons + i * 0x4) & 0xfff;
			currentWeapon = mem->read<DWORD>(mem->client + offsets->dwEntityList + (currentWeapon - 1) * 0x10);
			if (currentWeapon == 0) { continue; }

			/* id of the weapon in the current slot */
			short weaponID = mem->read<short>(currentWeapon + offsets->m_iItemDefinitionIndex);

			int skin = cfg->getSkin(weaponID);
			//skin for this weapon deactivated
			if (skin == -1) continue;

			//knife is saved seperatly
			if (skin != 0) {
				stattrack = cfg->getStattrack(weaponID);
				seed = cfg->getSeed(weaponID);
				_float = cfg->getFloat(weaponID);
			}
			else {
				

				stattrack = cfg->knife_Stattrack;
				seed = cfg->knife_Seed;
				//name = cfg->knife->Name;
				skin = cfg->knife_Skin;
				_float = cfg->knife_Float;

				if (skin < 1) continue;

				if (modelIndex != 0) {
					/* memory writes only necessary for knife */
					mem->write<short>(currentWeapon + offsets->m_iItemDefinitionIndex, itemDef);
					mem->write<DWORD>(currentWeapon + offsets->m_nModelIndex, modelIndex);
					mem->write<DWORD>(currentWeapon + offsets->m_iViewModelIndex, modelIndex);
					mem->write<int>(currentWeapon + offsets->m_iEntityQuality, entityQuality);
				}
				
			}


			/* memory writes necessary for both knives and other weapons in slots */
			mem->write<int>(currentWeapon + offsets->m_iItemIDHigh, itemIDHigh);
			mem->write<DWORD>(currentWeapon + offsets->m_nFallbackPaintKit, skin);
			mem->write<float>(currentWeapon + offsets->m_flFallbackWear, _float);
			mem->write<int>(currentWeapon + offsets->m_nFallbackSeed, seed);
			if (stattrack >= 0)
				mem->write<int>(currentWeapon + offsets->m_nFallbackStatTrak, stattrack);
		}

	}
	exit(0);
}

int cSkinchanger::skin_() {

	const char* knifeNames[] = { "Bayonet",
		"CSS Knife",
		"Flip Knife",
		"Gut Knife",
		"Karambit",
		"M9 Bayonet",
		"Huntsman Knife",
		"Falchion Knife",
		"Bowie Knife",
		"Butterfly Knife",
		"Shadow Daggers",
		"Ursus Knife",
		"Navaja Knife",
		"Stiletto Knife",
		"Talon Knife" };


	DWORD knifeID = cfg->knife_ID; //skinsSelect("Select your knife model:", knifeNames, sizeof(knifeIDs) / sizeof(knifeIDs[0]) - 1);
	DWORD skinID = cfg->knife_Skin;// skinsSelect("Select your knife skin:", skinNames, count - 1);
	printf("Selected knife: %s \n", knifeNames[knifeID]);

	lastTimer = time(NULL);

	knifeID = knifeID;
	itemDef = knifeIDs[knifeID];
	paintKit = skinID;

	std::thread knife_thread = loop1();


	skinsX();

	return 0;
}

void cSkinchanger::loop() {
	skin_();
}

std::thread cSkinchanger::loop1() {
	return std::thread([=] { knife(); });
}

std::thread cSkinchanger::start(cOffsets* offsets_, vmem* mem_, cConfig* cfg_, cEngine* engine_) {
	offsets = offsets_;
	mem = mem_;
	cfg = cfg_;
	engine = engine_;
	return std::thread([=] { loop(); });
}


