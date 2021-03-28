#ifndef OFFSETS_H
#define OFFSETS_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;



class cOffsets {
protected:

public:
	static DWORD offsets[128];

	#define FL_IN_AIR_STAND						256
	#define FL_ON_GROUND						257
	#define FL_IN_AIR_MOVING_TO_STAND			258
	#define FL_ON_GROUND_MOVING_TO_STAND		259
	#define FL_IN_AIR_MOVING_TO_CROUCH			260
	#define FL_ON_GROUND_MOVING_TO_CROUCH		261
	#define FL_IN_AIR_CROUCHED					262
	#define FL_ON_GROUND_CROUCHED				263

	//scanning
	DWORD dwEntityList,
	dwClientState,			
	dwLocalPlayer,
	dwViewMatrix,
	dwForceAttack,
	dwGlowObjectManager,
	dwForceJump,
	dwClientState_ViewAngles,
	dwGameRulesProxy,
	dwRadarBase,
	GlowPatch;

	//sometimes changing
	DWORD m_bSpotted,
	m_aimPunchAngle,
	m_dwBoneMatrix,
	m_hActiveWeapon,
	m_hMyWeapons,
	m_iItemDefinitionIndex,
	m_fFlags,
	m_vecOrigin,
	m_vecViewOffset,
	m_lifeState,
	m_iCrosshairId,
	m_iGlowIndex,
	dwClientState_State,
	dwSensitivityPtr,
	dwSensitivity;


	//skinchanger
	DWORD m_iAccountID,
	m_OriginalOwnerXuidLow,
	m_OriginalOwnerXuidHigh,
	m_iItemIDLow, //= m_iItemIDHigh + 4
	m_iItemIDHigh,
	m_nFallbackPaintKit,
	m_nFallbackSeed,
	m_flFallbackWear,
	m_nFallbackStatTrak,
	m_iEntityQuality,
	m_szCustomName,
	m_ArmorValue,
	m_iShotsFired,
	m_flFlashMaxAlpha,
	m_iTeamNum,
	m_iHealth,
	m_bSpottedByMask,
	m_bIsDefusing,
	m_bHasDefuser,
	m_bHasHelmet,
	m_vecVelocity,
	oEntityLoopDistance, // = 0x10
	m_bDormant;
	
	
	//server
	DWORD ForceUpdate,
	m_hViewModel,
	m_nModelIndex,
	m_iWorldModelIndex,
	m_iViewModelIndex,
	m_iWorldDroppedModelIndex,
	m_totalHitsOnServer,
	m_clrRender;



public:
	cOffsets();
	void init(json server, json scan);
};
#endif