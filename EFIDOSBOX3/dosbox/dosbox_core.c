#include <efi.h>
#include <efilib.h>

#include "dosbox_core.h"
#include "cpu.h"
#include "hello_com.h"

static uint8_t *mem = NULL;

void dosbox_init(void)
{
    if (!mem) {
        mem = AllocatePool(0x10000);   // 64 KB
        if (!mem) {
            Print(L"[DOS] Error: sin memoria\n");
            return;
        }
    }

    for (UINTN i = 0; i < 0x10000; i++)
        mem[i] = 0x00;

    cpu_reset(mem);
}

void dosbox_run(const uint8_t *program, UINTN size)
{
    Print(L"ENTRANDO EN DOSBOX_RUN\n");

    if (!mem)
        dosbox_init();

    program = HELLO_COM;
    size = HELLO_COM_len;

    for (UINTN i = 0; i < size; i++)
        mem[0x100 + i] = program[i];

    cpu_set_ip(0x100);

    Print(L"[DOS] Ejecutando...\n");

    while (cpu_get_ip() != 0xFFFF)
        cpu_step();

    Print(L"\n[DOS] Ejecución finalizada\n");
}
