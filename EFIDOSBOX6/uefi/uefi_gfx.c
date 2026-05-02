#include <efi.h>
#include <efilib.h>
#include "uefi_gfx.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;
UINT32 *gfx_fb = NULL;
UINTN gfx_width = 0, gfx_height = 0;

EFI_STATUS gfx_init(EFI_SYSTEM_TABLE *SystemTable) {
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    Print(L"gfx_init: buscando GOP...\n");

    EFI_STATUS st = LibLocateProtocol(&gopGuid, (void**)&gop);

    Print(L"gfx_init: LibLocateProtocol=%r\n", st);

    if (EFI_ERROR(st) || !gop) {
        Print(L"GOP no encontrado\n");
        gfx_fb = NULL;
        gfx_width = gfx_height = 0;
        return st;
    }

    gfx_width  = gop->Mode->Info->HorizontalResolution;
    gfx_height = gop->Mode->Info->VerticalResolution;
    gfx_fb = (UINT32*)gop->Mode->FrameBufferBase;

    Print(L"GOP OK %ux%u, FB=%lx\n", gfx_width, gfx_height, gop->Mode->FrameBufferBase);
    return EFI_SUCCESS;
}

void gfx_present() {
}
void uefi_print_char(char c) {
    CHAR16 buf[2];
    buf[0] = (CHAR16)c;
    buf[1] = 0;
    Print(buf);
}

void uefi_print(const char *s) {
    CHAR16 buf[256];
    int i = 0;

    while (*s && i < 255) {
        buf[i++] = (CHAR16)(*s++);
    }
    buf[i] = 0;

    Print(buf);
}
