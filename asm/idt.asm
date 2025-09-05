[bits 32]
global i686_IDT_load
i686_IDT_load:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    lidt [eax]

    leave
    ret
