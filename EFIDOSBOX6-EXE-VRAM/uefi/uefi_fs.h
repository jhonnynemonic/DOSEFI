#ifndef UEFI_FS_H
#define UEFI_FS_H

#include <efi.h>
#include <efilib.h>

EFI_STATUS fs_open_file(
    EFI_HANDLE ImageHandle,
    CHAR16 *Filename,
    EFI_FILE_PROTOCOL **OutFile
);

#endif
