#include "stdint.h"
#include "interrupts/idt.h"
#include "vga.h"
#include "keyboard.h"
#include "keys.h"

void initKeyboard(){
    capsOn = false;
    capsLock = false;
    irq_install_handler(1,&keyboardHandler);
}

void keyboardHandler(struct InterruptRegisters *regs){
    char scanCode = inPortB(0x60) & 0x7F; //What key is pressed
    char press = inPortB(0x60) & 0x80; //Press down, or released

    switch(scanCode){
        case 1:
        case 29:
        case 56:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 87:
        case 88:
            break;
        case 42:
            //shift key
            if (press == 0){
                capsOn = true;
            }else{
                capsOn = false;
            }
            break;
        case 58:
            if (!capsLock && press == 0){
                capsLock = true;
            }else if (capsLock && press == 0){
                capsLock = false;
            }
            break;
        default:
            if (press == 0){
                if (capsOn || capsLock){
                    terminal_putchar(uppercase[scanCode]);
                }else{
                    terminal_putchar(lowercase[scanCode]);
                }
            }
            
    }
    
}
