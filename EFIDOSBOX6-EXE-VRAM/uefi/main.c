#include "stdint.h"
#include <efi.h>
#include <efilib.h>
#include "dosbox_core.h"
#include "../uefi/uefi_gfx.h"

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"[UEFI] DOS Loader iniciado\n");

    gfx_init(SystemTable);
    dosbox_run(NULL, 0);
    gfx_present();

    Print(L"[UEFI] Ejecución finalizada\n");
    return EFI_SUCCESS;
}
