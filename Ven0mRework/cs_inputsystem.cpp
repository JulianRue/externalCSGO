#include "cs_inputsystem.h"
#include "mem.h"
#include "cs_interfaces.h"

extern vmem        mem;
extern cs_virtual_table cs_vt_inputsystem;
extern uint32_t         cs_nv_m_dwButton;
extern uint32_t         cs_nv_m_dwAnalog;
extern uint32_t         cs_nv_m_dwAnalogDelta;

bool inputsystem::IsButtonDown(CS_BUTTONCODE button)
{
    uint32_t v;

    v = mem.read<uint32_t>(cs_vt_inputsystem.address() + (((button >> 5 ) * 4) + cs_nv_m_dwButton));
    return (v >> (button & 31)) & 1;
}

vec2i inputsystem::GetMouseAnalog(void)
{
    return mem.read<vec2i>(cs_vt_inputsystem.address() + cs_nv_m_dwAnalog);
}

vec2i inputsystem::GetMouseAnalogDelta(void)
{
    return mem.read<vec2i>(cs_vt_inputsystem.address() + cs_nv_m_dwAnalogDelta);
}

