; hello.asm
org 0x100

start:
    mov ah, 9
    mov dx, msg
    int 21h        ; mostrar cadena

    int 20h        ; terminar programa

msg db "Hola desde UEFI DOS!$"
