ASM=nasm
CC=gcc
FLAGS=-g -m32 -fno-stack-protector -fno-builtin -c
SRC_DIR=src
BUILD_DIR=build

all: boot.obj gdts.obj kernel.obj gdt.obj kernel GOOS.iso run

boot.obj: $(SRC_DIR)/boot.asm
	@$(ASM) -f elf32 $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.obj
gdts.obj: $(SRC_DIR)/gdt.asm
	@$(ASM) -f elf32 $(SRC_DIR)/gdt.asm -o $(BUILD_DIR)/gdts.obj
kernel.obj: $(SRC_DIR)/kernel.c
	@$(CC) $(FLAGS) $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.obj
gdt.obj: $(SRC_DIR)/gdt.c
	@$(CC) $(FLAGS) $(SRC_DIR)/gdt.c -o $(BUILD_DIR)/gdt.obj
kernel: $(BUILD_DIR)/boot.obj $(BUILD_DIR)/kernel.obj
	@ld -m elf_i386 -T linker.ld -o kernel $(BUILD_DIR)/boot.obj $(BUILD_DIR)/kernel.obj $(BUILD_DIR)/gdts.obj $(BUILD_DIR)/gdt.obj
	@mv kernel GOOS/boot/kernel
GOOS.iso: GOOS/boot/kernel
	@grub-mkrescue -o GOOS.iso GOOS/
run: GOOS.iso
	@qemu-system-i386 GOOS.iso 