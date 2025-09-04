#include "gdt.h"
#include <stdint.h>

typedef struct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMid;
    uint8_t accessByte;
    uint8_t flags;
    uint8_t baseHigh;
}__attribute__((packed)) GDTEntry;

typedef struct {
    uint16_t limit;
    GDTEntry *gdt_ptr;
}__attribute__((packed)) GDTDesc;

typedef enum {
    GDT_ACCESS_CODE_READABLE            = 0x02,
    GDT_ACCESS_DATA_WRITEABLE           = 0x02,
    
    GDT_ACCESS_CONFORMING_BIT           = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL    = 0x00,
    GDT_ACCESS_DATA_DIRECTION_REVERSE   = 0x04,
    
    GDT_ACCESS_DATA_SEGMENT             = 0x10,
    GDT_ACCESS_CODE_SEGMENT             = 0x18,

    GDT_ACCESS_DESCRIPTOR_TSS           = 0x00,

    GDT_ACCESS_RING0                    = 0x00,
    GDT_ACCESS_RING1                    = 0x20,
    GDT_ACCESS_RING2                    = 0x40,
    GDT_ACCESS_RING3                    = 0x60,

    GDT_ACCESS_PRESENT                  = 0x80,
} GDT_ACCESS;

typedef enum {
    GDT_FLAG_16BIT          = 0x00,
    GDT_FLAG_32BIT          = 0x20,
    
    GDT_FLAG_GRANULARITY_1B = 0x00,
    GDT_FLAG_GRANULARITY_4K = 0x80
} GDT_FLAGS;

#define GDT_LIMIT_LOW(limit)                (limit & 0xFFFF)
#define GDT_BASE_LOW(base)                  (base  & 0xFFFF)
#define GDT_BASE_MID(base)                  ((base >> 16) & 0xFF)
#define GDT_FLAGS_LIMIT(limit, flags)       (((limit >> 16) & 0xF) | (flags & 0xF0))
#define GDT_BASE_HIGH(base)                 ((base >> 24) & 0xFF)
 
#define GDT_ENTRY(base, limit, access, flags)\
{       GDT_LIMIT_LOW(limit), \
       GDT_BASE_LOW(base), \
       GDT_BASE_MID(base), \
       access, \
       GDT_FLAGS_LIMIT(limit, flags), \
       GDT_BASE_HIGH(base), \
}
GDTEntry gdt_entry[] = {
    // NULL descriptor
    GDT_ENTRY(0, 0, 0, 0),

    // Kernel 32-bit code segment
    GDT_ENTRY(0, 
              0xFFFFF,
              (GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE),
              (GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K)),
    

    // Kernel 32-bit data segment
    GDT_ENTRY(0,
              0xFFFFF,
              (GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITEABLE),
              (GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K)),
};

GDTDesc gdt_descriptor = { sizeof(gdt_entry) - 1, gdt_entry};

void __attribute__((cdecl)) i686_GDT_Load(GDTDesc* descriptor, uint16_t codeSegment, uint16_t dataSegment);

void i686_GDT_init(){
    i686_GDT_Load(&gdt_descriptor, i686_GDT_CODE_SEGMENT, i686_GDT_DATA_SEGMENT);
}
