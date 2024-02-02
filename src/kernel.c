#include "gdt.h"
#include "vga.h"
#include "interrupts/idt.h"

void kmain(void);

void kmain(void){
    initGdt();
	initIdt();
	terminal_initialize();
	terminal_writestring("HelloWorld!\n");
}
