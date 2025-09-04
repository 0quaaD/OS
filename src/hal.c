#include "gdt.h"
#include "hal.h"
#include "idt.h"

void HAL_init(){
    i686_GDT_init();
    i686_IDT_init();
}
