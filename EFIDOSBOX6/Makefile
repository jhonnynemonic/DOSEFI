CC=gcc
LD=ld
OBJCOPY=objcopy
# Rutas GNU‑EFI (WSL)
EFIROOT = ~/gnu-efi-3.0.18

CFLAGS=-I $(EFIROOT)/inc -Iuefi -Idosbox -ffreestanding -fpic -fshort-wchar \
       -fno-stack-protector -fno-stack-check -mno-red-zone -maccumulate-outgoing-args

LDFLAGS = -shared -Bsymbolic -L $(EFIROOT)/x86_64/lib/ -L $(EFIROOT)/x86_64/gnuefi/ -L $(EFIROOT)/lib -T $(EFIROOT)/gnuefi/elf_x86_64_efi.lds $(EFIROOT)/gnuefi/crt0-efi-x86_64.o -lgnuefi -lefi

UEFI_OBJS=uefi/main.o uefi/uefi_gfx.o uefi/uefi_keyboard.o uefi/uefi_fs.o dosbox/noname_exe.o dosbox/int.o dosbox/memory.o
DOSBOX_OBJS=dosbox/dosbox_core.o dosbox/cpu.o

OBJS = $(UEFI_OBJS) $(DOSBOX_OBJS)

all: dosbox.efi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dosbox.so: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

dosbox.efi: dosbox.so
	$(OBJCOPY) -j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym \
    -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc \
    --target efi-app-x86_64 --subsystem=10 $< $@

clean:
	rm -f $(OBJS) dosbox.so dosbox.efi
