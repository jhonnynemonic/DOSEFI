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
