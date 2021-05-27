OSNAME = TotoOS

CC = gcc
LD = ld
OBJCP = objcopy

DIST_DIR = dist
DEPENDENCIES_DIR = dependencies

BOOTLOADER_CFLAGS = -Iinclude/bootloader/ -I$(DEPENDENCIES_DIR)/efi/inc -I$(DEPENDENCIES_DIR)/efi/inc/x86_64 -Wno-error=pragmas -mno-red-zone -mno-avx -fpic  -g -O2 -Wall -Wextra -Werror -fshort-wchar -fno-strict-aliasing -ffreestanding -fno-stack-protector -fno-stack-check -fno-stack-check -fno-merge-all-constants -Wno-error=unused-parameter -Wno-error=unused-variable -DCONFIG_x86_64 -DGNU_EFI_USE_MS_ABI -maccumulate-outgoing-args --std=c11 -D__KERNEL__
BOOTLOADER_LDFLAGS = -nostdlib --warn-common --no-undefined --fatal-warnings --build-id=sha1 -shared -Bsymbolic -L$(DEPENDENCIES_DIR)/efi/x86_64/lib -L$(DEPENDENCIES_DIR)/efi/x86_64/gnuefi
BOOTLOADER_LD_LIBRARIES = -lefi -lgnuefi /usr/lib/gcc/x86_64-linux-gnu/10/libgcc.a -T $(DEPENDENCIES_DIR)/efi/gnuefi/elf_x86_64_efi.lds
BOOTLOADER_OBJCP_FLAGS = -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .rel.* -j .rela.* -j .rel* -j .rela* -j .reloc --target efi-app-x86_64

BOOTLOADER_SRC_DIR = src/bootloader
BOOTLOADER_OBJ_DIR = build/bootloader
BOOTLOADER_SRC_FILES := $(shell find $(BOOTLOADER_SRC_DIR) -name '*.c')
BOOTLOADER_OBJ_FILES := $(patsubst $(BOOTLOADER_SRC_DIR)/%.c, $(BOOTLOADER_OBJ_DIR)/%.o, $(BOOTLOADER_SRC_FILES))

KERNEL_CFLAGS = -ffreestanding -Wno-write-strings -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Iinclude/kernel/
KERNEL_LDFLAGS = -T src/kernel/linker.ld -static -Bsymbolic -nostdlib

KERNEL_SRC_DIR = src/kernel
KERNEL_OBJ_DIR = build/kernel
KERNEL_SRC_FILES := $(shell find $(KERNEL_SRC_DIR) -name '*.cpp')
KERNEL_OBJ_FILES := $(patsubst $(KERNEL_SRC_DIR)/%.cpp, $(KERNEL_OBJ_DIR)/%.o, $(KERNEL_SRC_FILES))

# --------------------- Efi stuff -------------------------------
efi_compile:
	$(MAKE) -C dependencies/efi

efi_clean:
	$(MAKE) -C dependencies/efi clean

# --------------------- Bootloader stuff ------------------------

$(BOOTLOADER_OBJ_DIR)/%.o: $(BOOTLOADER_SRC_DIR)/%.c
	mkdir -p $(@D)

	$(CC) $(BOOTLOADER_CFLAGS) -c $^ -o $@

$(DIST_DIR)/bootloader.so: $(BOOTLOADER_OBJ_FILES)
	mkdir -p $(DIST_DIR)
	$(LD) $(BOOTLOADER_LDFLAGS) $(DEPENDENCIES_DIR)/efi/x86_64/gnuefi/crt0-efi-x86_64.o $^ -o $@ $(BOOTLOADER_LD_LIBRARIES)

$(DIST_DIR)/bootloader.efi: $(DIST_DIR)/bootloader.so
	$(OBJCP) $(BOOTLOADER_OBJCP_FLAGS) $^ $@
	rm $^

# ---------------------- Kernel stuff ----------------------------

$(KERNEL_OBJ_DIR)/%.o: $(KERNEL_SRC_DIR)/%.cpp
	mkdir -p $(@D)

	$(CC) $(KERNEL_CFLAGS) -c $^ -o $@

$(DIST_DIR)/kernel.elf: $(KERNEL_OBJ_FILES)
	mkdir -p $(DIST_DIR)

	$(LD) $(KERNEL_LDFLAGS) $^ -o $@

# ---------------------- Image Creation --------------------------

createimg: $(DIST_DIR)/bootloader.efi startup.nsh $(DIST_DIR)/kernel.elf
	dd if=/dev/zero of=$(DIST_DIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(DIST_DIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(DIST_DIR)/$(OSNAME).img ::/EFI
	mmd -i $(DIST_DIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(DIST_DIR)/$(OSNAME).img $(DIST_DIR)/bootloader.efi ::/EFI/BOOT
	mcopy -i $(DIST_DIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(DIST_DIR)/$(OSNAME).img $(DIST_DIR)/kernel.elf ::
	mcopy -i $(DIST_DIR)/$(OSNAME).img $(DEPENDENCIES_DIR)/fonts/zap-light16.psf ::

run: efi_compile createimg
	qemu-system-x86_64 -drive file=$(DIST_DIR)/$(OSNAME).img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(DEPENDENCIES_DIR)/OVMF/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(DEPENDENCIES_DIR)/OVMF/OVMF_VARS-pure-efi.fd" -net none

clean: efi_clean
	rm -r build
	rm -r dist
