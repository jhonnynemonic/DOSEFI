#include "cpu.h"

static CPUState cpu;
static uint8_t *mem;

static uint8_t mem_read8(uint32_t addr) {
    return mem[addr & 0xFFFFF];
}

void cpu_reset(uint8_t *memory)
{
    mem = memory;

    cpu.ax = cpu.bx = cpu.cx = cpu.dx = 0;
    cpu.si = cpu.di = cpu.bp = 0;
    cpu.sp = 0xFFFE;

    cpu.cs = 0x0000;
    cpu.ds = 0x0000;
    cpu.es = 0x0000;
    cpu.ss = 0x0000;

    cpu.ip = 0x0000;
    cpu.flags = 0x0200;
}

void cpu_set_ip(uint16_t ip)
{
    cpu.ip = ip;
}

uint16_t cpu_get_ip(void)
{
    return cpu.ip;
}

uint8_t cpu_peek_opcode(void)
{
    uint32_t addr = (cpu.cs << 4) + cpu.ip;
    return mem_read8(addr);
}

static uint8_t fetch8(void)
{
    uint32_t addr = (cpu.cs << 4) + cpu.ip;
    uint8_t v = mem_read8(addr);
    cpu.ip++;
    return v;
}

static void handle_int(uint8_t intnum)
{
    if (intnum == 0x20) {
        cpu.ip = 0xFFFF;
        return;
    }

    if (intnum == 0x21) {
        uint8_t ah = cpu.ax >> 8;

        if (ah == 0x09) {
            uint32_t addr = (cpu.ds << 4) + cpu.dx;

            while (1) {
                char c = mem_read8(addr++);
                if (c == '$') break;
                Print(L"%c", c);
            }
            return;
        }
    }

    Print(L"[CPU] INT %02x no implementado\n", intnum);
    cpu.ip = 0xFFFF;
}

void cpu_step(void)
{
    uint8_t op = fetch8();

    switch (op) {

        case 0x90: // NOP
            break;

        case 0xB0: // MOV AL,imm8
            cpu.ax = (cpu.ax & 0xFF00) | fetch8();
            break;

        case 0xB4: // MOV AH,imm8
            cpu.ax = (cpu.ax & 0x00FF) | (fetch8() << 8);
            break;

        case 0xBA: // MOV DX,imm16
            cpu.dx = fetch8() | (fetch8() << 8);
            break;

        case 0xCD: { // INT imm8
            uint8_t intnum = fetch8();
            handle_int(intnum);
            break;
        }

        default:
            Print(L"[CPU] Opcode %02x no implementado\n", op);
            cpu.ip = 0xFFFF;
            break;
    }
}
