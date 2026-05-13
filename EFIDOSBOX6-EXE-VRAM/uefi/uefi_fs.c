#include <efi.h>
#include <efilib.h>
#include "uefi_fs.h"

EFI_STATUS fs_open_file(
    EFI_HANDLE ImageHandle,
    CHAR16 *Filename,
    EFI_FILE_PROTOCOL **OutFile
){
    EFI_STATUS Status;

    //
    // 1. Buscar TODOS los SimpleFileSystemProtocol del sistema
    //
    UINTN Count = 0;
    EFI_HANDLE *Handles = NULL;

    Status = BS->LocateHandleBuffer(
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &Count,
        &Handles
    );

    if (EFI_ERROR(Status) || Count == 0) {
        Print(L"[FS] Error: no hay SimpleFileSystem\n");
        return Status;
    }

    //
    // 2. Probar cada FS hasta encontrar HELLO.COM
    //
    for (UINTN i = 0; i < Count; i++) {

        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFS = NULL;
        Status = BS->HandleProtocol(
            Handles[i],
            &gEfiSimpleFileSystemProtocolGuid,
            (VOID**)&SimpleFS
        );

        if (EFI_ERROR(Status) || !SimpleFS)
            continue;

        EFI_FILE_PROTOCOL *Root = NULL;
        Status = SimpleFS->OpenVolume(SimpleFS, &Root);
        if (EFI_ERROR(Status) || !Root)
            continue;

        //
        // Intentar abrir HELLO.COM en raíz
        //
        EFI_FILE_PROTOCOL *File = NULL;
        Status = Root->Open(
            Root,
            &File,
            Filename,               // "HELLO.COM"
            EFI_FILE_MODE_READ,
            0
        );

        if (!EFI_ERROR(Status) && File) {
            Print(L"[FS] Archivo abierto: %s\n", Filename);
            *OutFile = File;
            return EFI_SUCCESS;
        }

        //
        // Intentar abrir en EFI\BOOT\HELLO.COM
        //
        Status = Root->Open(
            Root,
            &File,
            L"EFI\\BOOT\\HELLO.COM",
            EFI_FILE_MODE_READ,
            0
        );

        if (!EFI_ERROR(Status) && File) {
            Print(L"[FS] Archivo abierto: EFI\\BOOT\\HELLO.COM\n");
            *OutFile = File;
            return EFI_SUCCESS;
        }
    }

    Print(L"[FS] Error: No se pudo abrir %s\n", Filename);
    return EFI_NOT_FOUND;
}
