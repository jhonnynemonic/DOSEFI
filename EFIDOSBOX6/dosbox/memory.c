#include <stdint.h>
#include "memory.h"

//uint8_t *mem;   // definido en dosbox_core.c

uint8_t mem_read8(uint32_t addr)
{
    if (addr >= 1024*1024)
        return 0;
    return mem[addr];
}

void mem_write8(uint32_t addr, uint8_t val)
{
    if (addr >= 1024*1024)
        return;
    mem[addr] = val;
}
