#include "Offsets.h"

cOffsets::cOffsets() {}

void cOffsets::init(json server, json scan) {
	try {
		dwEntityList = scan["dwEntityList"].get<DWORD>();
		dwClientState = scan["dwClientState"].get<DWORD>();
		dwLocalPlayer = scan["dwLocalPlayer"].get<DWORD>();
		dwLocalPlayer = 0xD3ABEC;
		dwViewMatrix = scan["dwViewMatrix"].get<DWORD>();
		dwForceAttack = scan["dwForceAttack"].get<DWORD>();
		dwGlowObjectManager = scan["dwGlowObjectManager"].get<DWORD>();
		dwForceJump = scan["dwForceJump"].get<DWORD>();
		dwClientState_ViewAngles = scan["dwClientState_ViewAngles"].get<DWORD>();
		dwRadarBase = scan["dwRadarBase"].get<DWORD>(); ;
		dwGameRulesProxy = scan["dwGameRulesProxy"].get<DWORD>();
		GlowPatch = scan["GlowPatch"].get<DWORD>();
	}
	catch (...) {
		std::cout << "Offset error1!\n";
		system("pause");
		exit(0);
	}



	if (server != NULL) {
		try {
			m_hMyWeapons = server["netvars"]["m_hMyWeapons"].get<DWORD>();
			m_iItemDefinitionIndex = server["netvars"]["m_iItemDefinitionIndex"].get<DWORD>();
			m_hActiveWeapon = server["netvars"]["m_hActiveWeapon"].get<DWORD>();
			m_iAccountID = server["netvars"]["m_iAccountID"].get<DWORD>();
			m_OriginalOwnerXuidLow = server["netvars"]["m_OriginalOwnerXuidLow"].get<DWORD>();
			m_OriginalOwnerXuidHigh = server["netvars"]["m_OriginalOwnerXuidHigh"].get<DWORD>();
			m_iItemIDHigh = server["netvars"]["m_iItemIDHigh"].get<DWORD>();
			m_iItemIDLow = m_iItemIDHigh + 4;
			m_nFallbackPaintKit = server["netvars"]["m_nFallbackPaintKit"].get<DWORD>();
			m_nFallbackSeed = server["netvars"]["m_nFallbackSeed"].get<DWORD>();
			m_flFallbackWear = server["netvars"]["m_flFallbackWear"].get<DWORD>();
			m_nFallbackStatTrak = server["netvars"]["m_nFallbackStatTrak"].get<DWORD>();
			m_iEntityQuality = server["netvars"]["m_iEntityQuality"].get<DWORD>();
			m_szCustomName = server["netvars"]["m_szCustomName"].get<DWORD>();
			m_ArmorValue = server["netvars"]["m_ArmorValue"].get<DWORD>();
			m_iShotsFired = server["netvars"]["m_iShotsFired"].get<DWORD>();
			m_flFlashMaxAlpha = server["netvars"]["m_flFlashMaxAlpha"].get<DWORD>();
			m_iTeamNum = server["netvars"]["m_iTeamNum"].get<DWORD>();
			m_iHealth = server["netvars"]["m_iHealth"].get<DWORD>();
			m_bSpottedByMask = server["netvars"]["m_bSpottedByMask"].get<DWORD>();
			m_bIsDefusing = server["netvars"]["m_bIsDefusing"].get<DWORD>();
			m_bHasDefuser = server["netvars"]["m_bHasDefuser"].get<DWORD>();
			dwClientState_State = server["signatures"]["dwClientState_State"].get<DWORD>();
			m_bHasHelmet = server["netvars"]["m_bHasHelmet"].get<DWORD>();
			m_vecVelocity = server["netvars"]["m_vecVelocity"].get<DWORD>();
			oEntityLoopDistance = 0x10;

			m_bDormant = server["signatures"]["m_bDormant"].get<DWORD>();
			dwSensitivity = server["signatures"]["dwSensitivity"].get<DWORD>();
			dwSensitivityPtr = server["signatures"]["dwSensitivityPtr"].get<DWORD>();
			m_iCrosshairId = server["netvars"]["m_iCrosshairId"].get<DWORD>();
		}
		catch (...) {
			std::cout << "Offset error2!\n";
			system("pause");
			exit(0);
		}
		try {
			ForceUpdate = server["custom"]["ForceUpdate"].get<DWORD>();
			m_hViewModel = server["netvars"]["m_hViewModel[0]"].get<DWORD>();
			m_nModelIndex = server["netvars"]["m_nModelIndex"].get<DWORD>();
			m_iWorldModelIndex = server["netvars"]["m_iWorldModelIndex"].get<DWORD>();
			m_iViewModelIndex = server["netvars"]["m_iViewModelIndex"].get<DWORD>();
			m_iWorldDroppedModelIndex = server["netvars"]["m_iWorldDroppedModelIndex"].get<DWORD>();
			m_totalHitsOnServer = server["netvars"]["m_totalHitsOnServer"].get<DWORD>();
			m_clrRender = server["netvars"]["m_clrRender"].get<DWORD>();
		}
		catch (...) {
			std::cout << "Offset error3!\n";
			system("pause");
			exit(0);
		}
	}
	

	
}