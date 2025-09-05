#pragma once
#include "stdint.h"

void inb();
void outb(uint16_t port, uint8_t val);

typedef struct {
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, userssp, ss; 
    
} INTREG;  
