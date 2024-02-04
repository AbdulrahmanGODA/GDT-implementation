#include "util.h"

void memorySet(void* dest, char val, uint32_t count){
    char* temp =(char*) dest;
    for(; count != 0; count --){
        *temp++ = val;
    }
}
void outPortB(uint16_t Port, uint8_t Value){
    /*
    This function outputs a byte of data to a specified I/O port.
    One of these I/O ports is connected to the PIC chips.
    So we are going to send data to that I/O PORT using assembly instruction outb.
    */
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}
char inPortB(uint16_t port){
    char rv;
    asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
    return rv;
}
