#include "idt.h"
#include <stdint.h>
#include "binary.h"

typedef struct {
    uint16_t offsetLow;
    uint16_t segmentSel;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offsetHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t limit;
    IDTEntry* idt_ptr;
} __attribute__((packed)) IDTDesc;


IDTEntry idt_entry[256];
IDTDesc idt_descriptor = {sizeof(idt_entry) - 1, idt_entry};

void __attribute__((cdecl)) i686_IDT_Load(IDTDesc* idt_descriptor);

void i686_IDT_SetGate(int interrupt, void* base, uint16_t segmentDesc, uint8_t flags){
    idt_entry[interrupt].offsetLow = ((uint32_t)base) & 0xFFFF;
    idt_entry[interrupt].segmentSel= segmentDesc;
    idt_entry[interrupt].reserved= 0;
    idt_entry[interrupt].flags= flags;
    idt_entry[interrupt].offsetHigh = ((uint32_t)base >> 16) & 0xFFFF;
}

void i686_IDT_EnableGate(int interrupt){
    FLAG_SET(idt_entry[interrupt].flags, IDT_FLAG_PRESENT);    
}

void i686_IDT_DisableGate(int interrupt){
    FLAG_UNSET(idt_entry[interrupt].flags, IDT_FLAG_PRESENT);    
}

void i686_IDT_init(){
    i686_IDT_Load(&idt_descriptor);
}
