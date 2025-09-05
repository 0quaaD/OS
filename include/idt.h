#pragma once
#include "stdint.h"
typedef struct {
    uint16_t offsetLow;
    uint16_t segmentSel;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offsetHigh;
}__attribute__((packed)) IDTEntry;

#define IDT_SEL     0x08
#define IDT_FLAG    0x8E

typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) IDTptr;

void initIDT();
void setIDTGate(uint32_t num, uint32_t handler, uint16_t selector, uint8_t flags);
