#ifndef CPU_H
#define CPU_H

#include <efi.h>
#include <efilib.h>

typedef struct {
    uint16_t ax, bx, cx, dx;
    uint16_t si, di, bp, sp;
    uint16_t cs, ds, es, ss;
    uint16_t ip;
    uint16_t flags;
} CPUState;

void    cpu_reset(uint8_t *memory);
void    cpu_set_ip(uint16_t ip);
void    cpu_step(void);

uint8_t  cpu_peek_opcode(void);
uint16_t cpu_get_ip(void);

#endif
