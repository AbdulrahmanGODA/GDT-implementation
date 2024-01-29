bits 32
section .multiBoot
    align 4
    dd 0x1BADB002
    dd 0x00000000
    dd -(0x1BADB002 + 0x00000000) ;check sum

section .text
    global start
    extern kmain
    start:
        mov esp, stack_space
        call kmain
    halt: hlt  
        jmp halt

section .bss
    align 16
    resb 16384
    stack_space: