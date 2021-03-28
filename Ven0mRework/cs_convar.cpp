#include "cs_convar.h"
#include "cs_interfaces.h"
#include "mem.h"
#include <string.h>

extern vmem        mem;
extern cs_virtual_table cs_vt_cvar;

SHORT_STRING cs_convar::GetName(void)
{
    return mem.read<SHORT_STRING>(self + 0xC);
}

void cs_convar::SetString(const char *v)
{
    SHORT_STRING a0;
    memcpy(&a0, v, strlen(v));
	mem.write<SHORT_STRING>(self + 0x24, a0);
}

void cs_convar::SetInt(int v)
{
	mem.write<uint32_t>(self + 0x30, v ^ self);
}

void cs_convar::SetFloat(float v)
{
	mem.write<uint32_t>(self + 0x2C, *(uint32_t*)&v ^ self);
}

SHORT_STRING cs_convar::GetString(void)
{
    return mem.read<SHORT_STRING>(self + 0x24);
}

int cs_convar::GetInt(void)
{
    return mem.read<int>(self + 0x30) ^ self;
}

float cs_convar::GetFloat(void)
{
    uint32_t v;
    v = mem.read<uint32_t>(self + 0x2C) ^ self;
    return *(float*)&v;
}

cs_convar cvar::find(const char *name)
{
    csptr_t a0;

    a0 = mem.read<csptr_t>(cs_vt_cvar.address() + 0x34);
    while ( (a0 = mem.read<csptr_t>(a0 + 0x4)) ) {
        if (!strcmp(name, mem.read<SHORT_STRING>(a0 + 0xc).value)) {
            return *(cs_convar*)&a0;
        }
    }
    return {};
}

