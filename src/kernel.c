#include "gdt.h"
#include "vga.h"
#include "interrupts/idt.h"
#include "keyboard.h"

void kmain(void);

void kmain(void){
    initGdt();
	initIdt();
	terminal_initialize();
	initKeyboard();
}
