#include "stdint.h"

void memorySet(void* dest, char var, uint32_t);
void outPortB(uint16_t Port, uint8_t Value);
char inPortB(uint16_t port);

struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi,
     esi, 
     ebp, 
     esp, 
     ebx, 
     edx, 
     ecx, 
     eax;
    uint32_t int_no, 
     err_code;
    uint32_t eip, 
     csm, 
     eflags, 
     useresp, 
     ss;
};