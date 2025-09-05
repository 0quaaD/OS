#include "gdt.h"


GDTEntry gdt_entry[5];
GDTptr gdt_ptr;

extern void gdt_flush(GDTptr* gdt_ptr);
void initGDT(){
    gdt_ptr.limit = (sizeof(GDTEntry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entry;

    // NULL segment
    setGDTGate(0, 0, 0, 0, 0);
    
    // Kernel code segment
    setGDTGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // Kernel data segment
    setGDTGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User code segment
    setGDTGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // User data segment
    setGDTGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    
    gdt_flush(&gdt_ptr);
}


void setGDTGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entry[num].baseLow = (base & 0xFFFF);
    gdt_entry[num].baseMid = ((base >> 16) & 0xFF);
    gdt_entry[num].baseHigh = ((base >> 24) & 0xFF);

    gdt_entry[num].limitLow = (limit & 0xFFFF);
    gdt_entry[num].flags = (limit >> 16) & 0x0F;
    gdt_entry[num].flags |= (gran & 0xF0);

    gdt_entry[num].accessByte = access;
}
