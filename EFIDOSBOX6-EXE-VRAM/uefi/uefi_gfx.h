#pragma once
#include <efi.h>
#include <stdint.h>

EFI_STATUS gfx_init(EFI_SYSTEM_TABLE *SystemTable);

void gfx_present();

extern UINT32 *gfx_fb;
extern UINTN gfx_width; 
extern UINTN gfx_height;

void uefi_print_char(char c);
void uefi_print(const char *s);

extern uint8_t vga_memory[320 * 200];
extern uint8_t video_mode;

void video_set_mode_13h();



