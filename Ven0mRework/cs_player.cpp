#include "cs_player.h"
#include "mem.h"
#include "cs_interfaces.h"

extern vmem mem;
extern csptr_t   cs_nv_dwEntityList;
extern uint32_t  cs_nv_m_iHealth;
extern uint32_t  cs_nv_m_vecViewOffset;
extern uint32_t  cs_nv_m_lifeState;
extern uint32_t  cs_nv_m_nTickBase;
extern uint32_t  cs_nv_m_vecVelocity;
extern uint32_t  cs_nv_m_vecPunch;
extern uint32_t  cs_nv_m_iFOV;
extern uint32_t  cs_nv_m_iTeamNum;
extern uint32_t  cs_nv_m_vecOrigin;
extern uint32_t  cs_nv_m_hActiveWeapon;
extern uint32_t  cs_nv_m_iShotsFired;
extern uint32_t  cs_nv_m_bIsScoped;
extern uint32_t  cs_nv_m_dwBoneMatrix;

int cs_player::GetTeam(void)
{
    return mem.read<int>(self + cs_nv_m_iTeamNum);
}

int cs_player::GetHealth(void)
{
    return mem.read<int>(self + cs_nv_m_iHealth);
}

int cs_player::GetLifeState(void)
{
    return mem.read<int>(self + cs_nv_m_lifeState);
}

int cs_player::GetTickCount(void)
{
    return mem.read<int>(self + cs_nv_m_nTickBase);
}

int cs_player::GetShotsFired(void)
{
    return mem.read<int>(self + cs_nv_m_iShotsFired);
}

bool cs_player::IsScoped(void)
{
    return mem.read<bool>(self + cs_nv_m_bIsScoped);
}

bool cs_player::IsDormant(void)
{
    csptr_t a;

    a = (csptr_t)(self + 0x8);
    return mem.read<bool>(a + mem.read<uint8_t>((*(cs_virtual_table*)&a).function(9) + 0x8));
}

csptr_t cs_player::GetWeapon(void)
{
    csptr_t v;

    v = mem.read<csptr_t>(self + cs_nv_m_hActiveWeapon);
    return mem.read<csptr_t>(cs_nv_dwEntityList + ((v & 0xFFF) - 1) * 0x10);
}

vec3 cs_player::GetOrigin(void)
{
    return mem.read<vec3>(self + cs_nv_m_vecOrigin);
}

vec3 cs_player::GetVecView(void)
{
    return mem.read<vec3>(self + cs_nv_m_vecViewOffset);
}

vec3 cs_player::GetEyePos(void)
{
    vec3 v, o, r;
    v = this->GetVecView();
    o = this->GetOrigin();
    r.x = v.x += o.x; r.y = v.y += o.y; r.z = v.z += o.z;
    return r;
}

vec3 cs_player::GetVecVelocity(void)
{
    return mem.read<vec3>(self + cs_nv_m_vecViewOffset);
}

vec3 cs_player::GetVecPunch(void)
{
    return mem.read<vec3>(self + cs_nv_m_vecPunch);
}

int cs_player::GetFov(void)
{
    return mem.read<int>(self + cs_nv_m_iFOV);
}

void cs_player::GetBoneMatrix(int index, matrix3x4_t *out)
{
	out = mem.read<matrix3x4_t>(mem.read<csptr_t>(self + cs_nv_m_dwBoneMatrix) + 0x30 * index);
}

bool cs_player::IsValid(void)
{
    int health = GetHealth();

    return self && GetLifeState() == 0 && health > 0 && health < 1337;
}

