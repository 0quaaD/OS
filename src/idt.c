#include "idt.h"
#include <stdint.h>
#include "binary.h"

typedef struct {
    uint16_t offsetLow;
    uint16_t segmentSel;
    uint8_t reserved;
    uint8_t flags;
    uint8_t offsetHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t limit;
    IDTEntry* idt_ptr;
} __attribute__((packed)) IDTDesc;


typedef enum {
    IDT_FLAG_GATE_TASK          = 0x5,
    IDT_FLAG_GATE_16BIT_INT     = 0x6,
    IDT_FLAG_GATE_16BIT_TRAP    = 0x7,
    IDT_FLAG_GATE_32BIT_INT     = 0xE,
    IDT_FLAG_GATE_32BIT_TRAP    = 0xF,

    IDT_FLAG_RING0              = (0 << 5),
    IDT_FLAG_RING1              = (1 << 5),
    IDT_FLAG_RING2              = (2 << 5),
    IDT_FLAG_RING3              = (3 << 5),

    IDT_FLAG_PRESENT            = 0x80
} IDT_FLAGS;
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
    FLAG_SET(idt_entry[interrupt].flags, IDT_FLAGS_PRESENT);    
}

void i686_IDT_DisableGate(int interrupt){
    FLAG_UNSET(idt_entry[interrupt].flags, IDT_FLAGS_PRESENT);    
}

void i686_IDT_init(){
    i686_IDT_Load(&idt_descriptor);
}
