#include "stdint.h"

    //64-bit long  
struct gdt_entry_struct{ 
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_flags;
    uint8_t base_high;
}__attribute__((packed));
    //48-bit long pointer stored in GDTR
    // 0 - 15 : limit
    // 16 - 47 : base address 
struct gdt_ptr_struct{
    uint16_t limit;
    unsigned int base;
}__attribute__((packed));
struct tss_entry_struct{
    uint32_t link; // 0 - 15 link 16 - 31 reserved
    uint32_t esp0; 
    uint32_t ss0; // 16 - 31 reserved
    uint32_t esp1; 
    uint32_t ss1; // 16 - 31 reserved
    uint32_t esp2; 
    uint32_t ss2; // 16 - 31 reserved
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es; // 16 - 31 reserved 
    uint32_t cs; // 16 - 31 reserved 
    uint32_t ss; // 16 - 31 reserved 
    uint32_t ds; // 16 - 31 reserved 
    uint32_t fs; // 16 - 31 reserved 
    uint32_t gs; // 16 - 31 reserved 
    uint32_t ldtr; // 16 - 31 reserved 
    uint32_t iopb; // 0 - 15 reserved
    uint32_t ssp; 
}__attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0);