#ifndef ESP_H
#define ESP_H

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

class cEsp {
protected:


public:
	DWORD a;
	cEsp();

public:
	std::thread start(cOffsets *offsets_, vmem *mem_, cConfig* cfg_, cEngine* engine_);

private:
	cOffsets *offsets;
	vmem *mem;
	cConfig* cfg;
	cEngine* engine;

	void loop();
	void tick();
	

	struct rgba {
		float r, g, b, a;

	};

	struct glowStruct {
		float r;
		float g;
		float b;
		float a;
		unsigned char      unk0[0x10];
		bool               m_bRenderWhenOccluded = true;	//0024
		bool               m_bRenderWhenUnoccluded = false;	//0025
	};

	struct RenderWhen {
		bool rwo;
		bool rwuo;
	};

	//backup format
	struct bg {
		char backup_[235];
	}backup;

	typedef struct GlowObjectDefinition_t
	{
		DWORD              m_pEntity;				//0000
		float              m_flGlowRed;				//0004
		float              m_flGlowGreen;			//0008
		float              m_flGlowBlue;			//000C
		float              m_flGlowAlpha;			//0010
		unsigned char      unk0[0x10];				//0014
		bool               m_bRenderWhenOccluded;	//0024
		bool               m_bRenderWhenUnoccluded;	//0025
		unsigned char      unk2[0x12];				//0026
	} GlowObjectDefinition;							//0038

	typedef struct GlowObjectManager_t
	{
		GlowObjectDefinition* DataPtr;	    //0000
		unsigned int Max;                   //0004
		unsigned int unk02;                 //0008
		unsigned int Count;                 //000C
		unsigned int DataPtrBack;			//0010
		int m_nFirstFreeSlot;				//0014
		unsigned int unk1;					//0018
		unsigned int unk2;					//001C
		unsigned int unk3;					//0020
		unsigned int unk4;					//0024
		unsigned int unk5;					//0028
	} GlowObjectManager;



	rgba healthColor(bool myteam, int health);





	enum ClassID_t {
		cai_basenpc = 0,
		cak47,
		cbaseanimating,
		cbaseanimatingoverlay,
		cbaseattributableitem,
		cbasebutton,
		cbasecombatcharacter,
		cbasecombatweapon,
		cbasecsgrenade,
		cbasecsgrenadeprojectile,
		cbasedoor,
		cbaseentity,
		cbaseflex,
		cbasegrenade,
		cbaseparticleentity,
		cbaseplayer,
		cbasepropdoor,
		cbaseteamobjectiveresource,
		cbasetempentity,
		cbasetoggle,
		cbasetrigger,
		cbaseviewmodel,
		cbasevphysicstrigger,
		cbaseweaponworldmodel,
		cbeam,
		cbeamspotlight,
		cbonefollower,
		cbrc4target,
		cbreachcharge,
		cbreachcharge1,
		cbreachchargeprojectile,
		cbreakableprop,
		cbreakablesurface,
		cbumpmine,
		cbumpmineprojectile,
		cc4,
		ccascadelight,
		cchicken,
		ccolorcorrection,
		ccolorcorrectionvolume,
		ccsgamerulesproxy,
		ccsplayer,
		ccsplayerresource,
		ccsragdoll,
		ccsteam,
		cdangerzone,
		cdangerzonecontroller,
		cdeagle,
		cdecoygrenade,
		cdecoyprojectile,
		cdrone,
		cdronegun,
		cdynamiclight,
		cdynamicprop,
		ceconentity,
		ceconwearable,
		cembers,
		centitydissolve,
		centityflame,
		centityfreezing,
		centityparticletrail,
		cenvambientlight,
		cenvdetailcontroller,
		cenvdofcontroller,
		cenvgascanister,
		cenvparticlescript,
		cenvprojectedtexture,
		cenvquadraticbeam,
		cenvscreeneffect,
		cenvscreenoverlay,
		cenvtonemapcontroller,
		cenvwind,
		cfeplayerdecal,
		cfirecrackerblast,
		cfiresmoke,
		cfiretrail,
		cfish,
		cfists,
		cflashbang,
		cfogcontroller,
		cfootstepcontrol,
		cfunc_dust,
		cfunc_lod,
		cfuncareaportalwindow,
		cfuncbrush,
		cfuncconveyor,
		cfuncladder,
		cfuncmonitor,
		cfuncmovelinear,
		cfuncoccluder,
		cfuncreflectiveglass,
		cfuncrotating,
		cfuncsmokevolume,
		cfunctracktrain,
		cgamerulesproxy,
		cgrassburn,
		chandletest,
		chegrenade,
		chostage,
		chostagecarriableprop,
		cincendiarygrenade,
		cinferno,
		cinfoladderdismount,
		cinfomapregion,
		cinfooverlayaccessor,
		citem_healthshot,
		citemcash,
		citemdogtags,
		cknife,
		cknifegg,
		clightglow,
		cmaterialmodifycontrol,
		cmelee,
		cmolotovgrenade,
		cmolotovprojectile,
		cmoviedisplay,
		cparadropchopper,
		cparticlefire,
		cparticleperformancemonitor,
		cparticlesystem,
		cphysbox,
		cphysboxmultiplayer,
		cphysicsprop,
		cphysicspropmultiplayer,
		cphysmagnet,
		cphyspropammobox,
		cphysproplootcrate,
		cphyspropradarjammer,
		cphyspropweaponupgrade,
		cplantedc4,
		cplasma,
		cplayerping,
		cplayerresource,
		cpointcamera,
		cpointcommentarynode,
		cpointworldtext,
		cposecontroller,
		cpostprocesscontroller,
		cprecipitation,
		cprecipitationblocker,
		cpredictedviewmodel,
		cprop_hallucination,
		cpropcounter,
		cpropdoorrotating,
		cpropjeep,
		cpropvehicledriveable,
		cragdollmanager,
		cragdollprop,
		cragdollpropattached,
		cropekeyframe,
		cscar17,
		csceneentity,
		csensorgrenade,
		csensorgrenadeprojectile,
		cshadowcontrol,
		cslideshowdisplay,
		csmokegrenade,
		csmokegrenadeprojectile,
		csmokestack,
		csnowball,
		csnowballpile,
		csnowballprojectile,
		cspatialentity,
		cspotlightend,
		csprite,
		cspriteoriented,
		cspritetrail,
		cstatueprop,
		csteamjet,
		csun,
		csunlightshadowcontrol,
		csurvivalspawnchopper,
		ctablet,
		cteam,
		cteamplayroundbasedrulesproxy,
		ctearmorricochet,
		ctebasebeam,
		ctebeamentpoint,
		ctebeaments,
		ctebeamfollow,
		ctebeamlaser,
		ctebeampoints,
		ctebeamring,
		ctebeamringpoint,
		ctebeamspline,
		ctebloodsprite,
		ctebloodstream,
		ctebreakmodel,
		ctebspdecal,
		ctebubbles,
		ctebubbletrail,
		cteclientprojectile,
		ctedecal,
		ctedust,
		ctedynamiclight,
		cteeffectdispatch,
		cteenergysplash,
		cteexplosion,
		ctefirebullets,
		ctefizz,
		ctefootprintdecal,
		ctefoundryhelpers,
		ctegaussexplosion,
		cteglowsprite,
		cteimpact,
		ctekillplayerattachments,
		ctelargefunnel,
		ctemetalsparks,
		ctemuzzleflash,
		cteparticlesystem,
		ctephysicsprop,
		cteplantbomb,
		cteplayeranimevent,
		cteplayerdecal,
		cteprojecteddecal,
		cteradioicon,
		cteshattersurface,
		cteshowline,
		ctesla,
		ctesmoke,
		ctesparks,
		ctesprite,
		ctespritespray,
		ctest_proxytoggle_networkable,
		ctesttraceline,
		cteworlddecal,
		ctriggerplayermovement,
		ctriggersoundoperator,
		cvguiscreen,
		cvotecontroller,
		cwaterbullet,
		cwaterlodcontrol,
		cweaponaug,
		cweaponawp,
		cweaponbaseitem,
		cweaponbizon,
		cweaponcsbase,
		cweaponcsbasegun,
		cweaponcycler,
		cweaponelite,
		cweaponfamas,
		cweaponfiveseven,
		cweapong3sg1,
		cweapongalil,
		cweapongalilar,
		cweaponglock,
		cweaponhkp2000,
		cweaponm249,
		cweaponm3,
		cweaponm4a1,
		cweaponmac10,
		cweaponmag7,
		cweaponmp5navy,
		cweaponmp7,
		cweaponmp9,
		cweaponnegev,
		cweaponnova,
		cweaponp228,
		cweaponp250,
		cweaponp90,
		cweaponsawedoff,
		cweaponscar20,
		cweaponscout,
		cweaponsg550,
		cweaponsg552,
		cweaponsg556,
		cweaponshield,
		cweaponssg08,
		cweapontaser,
		cweapontec9,
		cweapontmp,
		cweaponump45,
		cweaponusp,
		cweaponxm1014,
		cworld,
		cworldvguitext,
		dusttrail,
		movieexplosion,
		particlesmokegrenade,
		rockettrail,
		smoketrail,
		sporeexplosion,
		sporetrail,
	};

	//pistols
	const int Desert_Eagle = cdeagle;
	const int Five_Seven = cweaponfiveseven;
	const int Tec_9 = cweapontec9;
	const int Zeus = cweapontaser;
	const int P250 = cweaponp250;
	const int Glock = cweaponglock;
	const int P2000 = cweaponhkp2000;
	const int Usp_s = cweaponusp;
	const int dual = cweaponelite;

	//rifles
	const int AK_47 = cak47;
	const int AUG = cweaponaug;
	const int SG_553 = cweaponsg556;
	const int M4A1_S = cweaponm4a1;
	const 	int famas = cweaponfamas;
	const 	int Galil = cweapongalilar;

	//smg
	const 	int P90 = cweaponp90;
	const 	int UMP_45 = cweaponump45;
	const 	int pp_bizon = cweaponbizon;
	const 	int Mac10 = cweaponmac10;
	const int Mp7 = cweaponmp7;
	const 	int Mp9 = cweaponmp9;


	//sniper
	const 	int AWP = cweaponawp;
	const 	int G35G1 = cweapong3sg1;
	const 	int SSG_08 = cweaponssg08;
	const int SCAR_20 = cweaponscar20;

	//heavy
	const int M249 = cweaponm249;
	const int Negev = cweaponnegev;

	//shotgun
	const int Mag7 = cweaponmag7;
	const int Nova = cweaponnova;
	const int SawedOff = cweaponsawedoff;
	const int XM1014 = cweaponxm1014;

	const int player = ccsplayer;


	const 	int Flashbang_air = cflashbang;
	const	int Grenade_air = cbasecsgrenadeprojectile;
	const	int Smoke_air = csmokegrenadeprojectile;
	const 	int Molotov_air = cmolotovprojectile;
	const 	int Decoy_air = cdecoyprojectile;
	const 	int Incendiary_air = cincendiarygrenade;
	const 	int C4_1 = cc4;
	const	int C4_planted = cplantedc4;			//planted

	const int Grenade_ground = chegrenade;
	const int Molotov_ground = cmolotovgrenade;
	const int Smoke_ground = csmokegrenade;
	const int Decoy_ground = cdecoygrenade;

	const int kit = cbaseanimating;

	const char * idToName(int number) {
		if (number == Desert_Eagle)	return "Deagle";
		else if (number == dual)			return "Dual Berettas";
		else if (number == Five_Seven)		return "Five Seven";
		else if (number == Glock)			return "Glock";
		else if (number == P2000)			return "P2000";
		else if (number == P250)			return "P250";   // p250 == cz
		else if (number == Desert_Eagle)	return "Deagle"; //revolver == deagle
		else if (number == Tec_9)			return "Tec 9";
		else if (number == Usp_s)			return "USP-S";
		else if (number == Zeus)			return "Zeus";
		else if (number == AK_47)			return "AK 47";
		else if (number == M4A1_S)			return "M4";	//m4a4 == m4a1-s
		else if (number == Galil)			return "Galil";
		else if (number == famas)			return "Famas";
		else if (number == SG_553)			return "SG 553";
		else if (number == AUG)			return "AUG";
		else if (number == SSG_08)			return "SSG 08";
		else if (number == AWP)			return "AWP";
		else if (number == SCAR_20)		return "Scar 20";
		else if (number == G35G1)			return "G35G1";
		else if (number == SawedOff)		return "Sawed Off";
		else if (number == XM1014)			return "XM1014";
		else if (number == Mag7)			return "Mag 7";
		else if (number == Nova)			return "Nova";
		else if (number == M249)			return "M249";
		else if (number == Negev)			return "Negev";
		else if (number == Mp7)			return "MP7";
		else if (number == Mp9)			return "MP9";
		else if (number == pp_bizon)		return "PP Bizon";
		else if (number == Mac10)			return "MAC-10";
		else if (number == P90)			return "P90";
		else if (number == UMP_45)			return "UMP-45";
		else if (number == Flashbang_air)	return "Flash";
		else if (number == Grenade_air)	return "Nade";
		else if (number == Grenade_ground)	return "Nade";
		else if (number == Smoke_air)		return "Smoke";
		else if (number == Smoke_ground)	return "Smoke";
		else if (number == Molotov_air)	return "Molly";
		else if (number == Molotov_ground)	return "Molly";
		else if (number == Decoy_air)		return "Decoy";
		else if (number == Decoy_ground)	return "Decoy";
		else if (number == Incendiary_air)	return "Molly";
		else								return "Unknown";
	}

	bool isWeapon(int id) {
		if (id == Desert_Eagle ||
			id == Five_Seven ||
			id == Tec_9 ||
			id == Zeus ||
			id == P250 ||
			id == Glock ||
			id == P2000 ||
			id == Usp_s ||
			id == AK_47 ||
			id == AUG ||
			id == SG_553 ||
			id == M4A1_S ||
			id == famas ||
			id == Galil ||
			id == P90 ||
			id == UMP_45 ||
			id == pp_bizon ||
			id == Mac10 ||
			id == Mp7 ||
			id == Mp9 ||
			id == AWP ||
			id == G35G1 ||
			id == SSG_08 ||
			id == SCAR_20 ||
			id == M249 ||
			id == Negev ||
			id == Mag7 ||
			id == Nova ||
			id == SawedOff ||
			id == XM1014
			) return true;
		else
			return false;
	}

	bool isFlyingGrenade(int id) {
		if (id == Flashbang_air ||
			id == Grenade_air ||
			id == Smoke_air ||
			id == Molotov_air ||
			id == Decoy_air ||
			id == Incendiary_air
			)return true;
		else
			return false;
	}

	bool isGroundGrenade(int id) {
		if (id == Grenade_ground ||
			id == Molotov_ground ||
			id == Smoke_ground ||
			id == Decoy_ground
			)return true;
		else
			return false;
	}


};
#endif