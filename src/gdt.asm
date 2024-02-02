global gdt_flush
global tss_flush

gdt_flush:
    mov eax,[esp+4] 
    ;mov the 32bit address of the pointer from the top of the stack
    lgdt [eax] 
    ;load the 48bit GDTR with the values pointed by that pointer (16bit for the limit and 32bit for the base).
    mov eax, 0x10 
    ;establishing a flat memory model by pointing all segment registers to the same segment with offset 0x10 into GDT.
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush
flush: ret
tss_flush:
    mov ax, 0x2B
    ltr ax
    ret