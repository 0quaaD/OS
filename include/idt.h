#pragma once

#include <stdint.h>

typedef enum {
    // Gate flags
    IDT_FLAG_TASK_GATE  = 0x5,
    IDT_FLAG_16BIT_INT  = 0x6,
    IDT_FLAG_16BIT_TRAP = 0x7,
    IDT_FLAG_32BIT_INT  = 0xE,
    IDT_FLAG_32BIT_TRAP = 0xF,

    // Descriptor privledge levels
    IDT_FLAG_RING0 = (0 << 5),
    IDT_FLAG_RING1 = (1 << 5),
    IDT_FLAG_RING2 = (2 << 5),
    IDT_FLAG_RING3 = (3 << 5),

    // Present gate
    IDT_FLAG_PRESENT = (1 << 7)
} IDTFlags;

#define FLAG_SET(x, flags)      x |= (flags)
#define FLAG_UNSET(x, flags)    x &= ~(flags)
#define idt_present             IDT_FLAG_PRESENT

void i686_IDT_init();
void i686_IDT_DisableGate(int interrupt);
void i686_IDT_EnableGate(int interrupt);
void i686_IDT_SetGate(int interrupt, void* base, uint16_t segmentDesc, uint8_t flags);

