#include "gdt.h"
#include "vga.h"

void kmain(void);

void kmain(void){
    initGdt();
	terminal_initialize();
 
	terminal_writestring("I can't believe that i did it ... it works ..... finally it works ... my back hurts so much ... maybe i should take a break ... yeah yeah a break ... that would be great ... ahhhh.");
}
