#include "gdt.h"
#include "vga.h"

void kmain(void);

void kmain(void){
    initGdt();
	terminal_initialize();
	terminal_writestring("Terminal> cd /root");
}
