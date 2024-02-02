ASM=nasm
CC=gcc
FLAGS=-m32 -fno-stack-protector -fno-builtin -c
SRC_DIR=src
BUILD_DIR=build

all: boot.obj gdts.obj idts.obj kernel.obj gdt.obj vga.obj util.obj idt.obj kernel GOOS.iso run 

boot.obj: $(SRC_DIR)/boot.asm
	@$(ASM) -f elf32 $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.obj
gdts.obj: $(SRC_DIR)/gdt.asm
	@$(ASM) -f elf32 $(SRC_DIR)/gdt.asm -o $(BUILD_DIR)/gdts.obj
idts.obj: $(SRC_DIR)/interrupts/idt.asm
	@$(ASM) -f elf32 $(SRC_DIR)/interrupts/idt.asm -o $(BUILD_DIR)/idts.obj

kernel.obj: $(SRC_DIR)/kernel.c
	@$(CC) $(FLAGS) $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.obj
gdt.obj: $(SRC_DIR)/gdt.c
	@$(CC) $(FLAGS) $(SRC_DIR)/gdt.c -o $(BUILD_DIR)/gdt.obj
vga.obj: $(SRC_DIR)/vga.c
	@$(CC) $(FLAGS) $(SRC_DIR)/vga.c -o $(BUILD_DIR)/vga.obj
util.obj: $(SRC_DIR)/util.c
	@$(CC) $(FLAGS) $(SRC_DIR)/util.c -o $(BUILD_DIR)/util.obj
idt.obj: $(SRC_DIR)/interrupts/idt.c
	@$(CC) $(FLAGS) $(SRC_DIR)/interrupts/idt.c -o $(BUILD_DIR)/idt.obj

kernel: $(BUILD_DIR)/boot.obj $(BUILD_DIR)/kernel.obj
	@ld -m elf_i386 -T linker.ld -o kernel $(BUILD_DIR)/boot.obj $(BUILD_DIR)/kernel.obj $(BUILD_DIR)/gdts.obj $(BUILD_DIR)/gdt.obj $(BUILD_DIR)/vga.obj $(BUILD_DIR)/util.obj $(BUILD_DIR)/idts.obj $(BUILD_DIR)/idt.obj
	
	@mv kernel GOOS/boot/kernel
GOOS.iso: GOOS/boot/kernel
	@grub-mkrescue -o GOOS.iso GOOS/
run: GOOS.iso
	@qemu-system-i386 GOOS.iso 