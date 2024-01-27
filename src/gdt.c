#include "gdt.h"

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct)*5) - 1;
    gdt_ptr.base = &gdt_entries;
    setGdtGate(0,0,0,0,0); //null segment
    setGdtGate(1,0,0xFFFFFFFF,0X9A,0xCF); //kernel Code
    setGdtGate(2,0,0xFFFFFFFF,0X92,0xCF); //kernel Data
    setGdtGate(3,0,0xFFFFFFFF,0XFA,0xCF); //user Code
    setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF); //user Data

    gdt_flush(&gdt_ptr);
}
void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].limit_flags = (limit >> 16) & 0x0F;
    gdt_entries[num].limit_flags |= (gran & 0xF0);

    gdt_entries[num].access = access;
}