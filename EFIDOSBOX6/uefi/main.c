#include "stdint.h"
#include <efi.h>
#include <efilib.h>
#include "dosbox_core.h"

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"[UEFI] DOS Loader iniciado\n");

    dosbox_run(NULL, 0);

    Print(L"[UEFI] Ejecución finalizada\n");
    return EFI_SUCCESS;
}
