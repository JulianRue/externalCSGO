#include "Esp.h"

cEsp::cEsp() {

}

std::thread cEsp::start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_) {
	offsets = offsets_;
	mem = mem_;
	cfg = cfg_;
	engine = engine_;
	
	//memory backup, zum wiederherstellen
	backup = mem->read<bg>(mem->client + offsets->GlowPatch);

	//memory part überschreiben, damit glow für immer bleibt
	mem->write<BYTE>(mem->client + offsets->GlowPatch, 0xEB);
	
	return std::thread([=] { loop(); });
}

void cEsp::loop() {
	int count = 0;
	for (;; Sleep(10)) {
		
		engine->update();

		if (!engine->isIngame) {
			std::cout << "Is not ingame!\n";
			continue;
		}

		if (count % 10 == 0 && count > 0) {
			tick();
			count = 0;
		}
			
		if (engine->exit) {
			break;
		}
		
		count++;
	}
	
	mem->write<bg>(mem->client + offsets->GlowPatch, backup);
}

cEsp::rgba cEsp::healthColor(bool myteam, int health) {
	if (myteam) {
		return rgba{ 0, 1.f - (health / 100.f), 1.f, 1.f };
	}
	else {
		return rgba{ 1.f - (health / 100.f), health / 100.f, 0.f, 1.f };
	}
}

void cEsp::tick() {

	DWORD objGlowArray = mem->read<DWORD>(mem->client + offsets->dwGlowObjectManager);
	DWORD objCount = mem->read<DWORD>(mem->client + offsets->dwGlowObjectManager + 4);


	if (objGlowArray == NULL) {
		std::cout << "objGlowArray -> " << objGlowArray << "\n";
		std::cout << "Glow count -> " << objCount << "\n";
		return;
	}

	if (objCount > 1000)
		return;

	for (int i = 0; i < objCount; i++)
	{
		
		//GlowObjectDefinition glowObj;

		//glowObj.m_pEntity = mem->read<DWORD>(mem->client + offsets->dwEntityList + i * offsets->oEntityLoopDistance);
			
		DWORD mObj = objGlowArray + i * sizeof(GlowObjectDefinition);
		GlowObjectDefinition glowObj = mem->read<GlowObjectDefinition>(mObj);
		if (!glowObj.m_pEntity)
			continue;

		DWORD classID = mem->GetClassID(glowObj.m_pEntity);
		
		if (classID == C4_planted) {
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 1.f, 1.f, 0, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (isGroundGrenade(classID)) {
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 0, 1.f, 1.f, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (isFlyingGrenade(classID)) {
			//all working
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 1.f, 0, 1.f, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (isWeapon(classID)) {
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 1.f, 0, 0, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (C4_1 == classID) {
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 0, 1.f, 0, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (kit == classID) {
			mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 1.f, 1.f, 0, 1.f });
			mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
		}
		else if (classID == player) {

			int health = mem->read<int>(glowObj.m_pEntity + offsets->m_iHealth);
			if (health < 1 || health > 100) {
				continue;
			}

			int team = mem->read<int>(glowObj.m_pEntity + offsets->m_iTeamNum);

			if (team == engine->team) {
				if (cfg->esp_team_health) {
					mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), healthColor(true, health));
				}
				else {
					mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 0, 0, 1.f, 1.f });
				}
				mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
			}
			else {
				if (cfg->esp_enemy_health) {
					mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), healthColor(false,health));
				}
				else {
					mem->write<rgba>((objGlowArray + (i * 0x38) + 0x4), rgba{ 1.f, 0, 0, 1.f });
				}
				mem->write<RenderWhen>((objGlowArray + (i * 0x38) + 0x24), RenderWhen{ true,false });
			}
		}
		
	}
	
	//glow patch rückgängig machen 
	//mem->write<bg>(mem->client + offsets->GlowPatch, backup);
	
}