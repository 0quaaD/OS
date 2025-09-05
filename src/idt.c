#include "idt.h"

IDTEntry idt_entry[256];
IDTptr idt_ptr;

extern void idt_flush(IDTptr* idt_ptr);
extern void defaultISR();

void initIDT(){
    for(int i=0; i< 256;i++){
        setIDTGate(i, (uint32_t)defaultISR,0x08, 0x8E);
    }

    idt_ptr.limit = (sizeof(IDTEntry) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt_entry;
    idt_flush(&idt_ptr);
    
}

void setIDTGate(uint32_t num, uint32_t handler, uint16_t selector, uint8_t flags){
       idt_entry[num].offsetLow = handler & 0xFFFF;
       idt_entry[num].segmentSel = selector,
       idt_entry[num].reserved = 0,
       idt_entry[num].flags = flags,
       idt_entry[num].offsetHigh = (handler >> 16) & 0xFFFF;
}

