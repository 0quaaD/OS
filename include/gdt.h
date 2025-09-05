#pragma once
#include "stdint.h"

typedef struct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMid;
    uint8_t accessByte;
    uint8_t flags;
    uint8_t baseHigh;
} __attribute__((packed)) GDTEntry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) GDTptr;

void initGDT();
void setGDTGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
