#pragma once
#include <efi.h>

EFI_STATUS gfx_init(EFI_SYSTEM_TABLE *SystemTable);
void gfx_present();
extern UINT32 *gfx_fb;
extern UINTN gfx_width, gfx_height;


