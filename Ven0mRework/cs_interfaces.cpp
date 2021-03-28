#include "cs_interfaces.h"
#include "mem.h"
#include <string.h>

extern vmem mem;

csptr_t cs_virtual_table::address(void) const
{
    return self;
}

csptr_t cs_virtual_table::function(int index)
{
    return mem.read<csptr_t>(mem.read<csptr_t>(self) + index * 4);
}

cs_virtual_table cs_interface_reg::find(const char *name)
{
    csptr_t a0 = self, a1[30];

    do {
		mem.read(mem.read<csptr_t>(a0 + 0x4), &a1, sizeof(a1));
        if ((_stricmp((const char *)a1, name) >> 5) == 1) {
            return mem.read<cs_virtual_table>(mem.read<csptr_t>(a0) + 1);
        }
    } while((a0 = mem.read<csptr_t>(a0 + 0x8)));
    throw name;
}

cs_interface_reg interfaces::find(const wchar_t *module_name)
{
    uintptr_t v;

    v = mem.find_export(cs_p.find_module(module_name), "CreateInterface");
    if  (v == 0)
        throw module_name;
    return mem.read<cs_interface_reg>(v - 0x6A);
}

