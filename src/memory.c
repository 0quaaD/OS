#include "memory.h"

void* memset(void* dest, uint8_t value, uint32_t count){
    uint8_t *ptr = (uint8_t*)dest;
    for(uint32_t i=0;i<count;i++){
        ptr[i] = value;    
    }
    return dest;
}

void* memcpy(void* dest, const void* src, uint32_t count){
    uint8_t *d = (uint8_t*)dest;
    const uint8_t *s = (const uint8_t *)src;
    for(uint32_t i = 0;i < count; i++)
        d[i] = s[i];
    return dest;
    
}
