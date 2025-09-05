#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "vga.h"
#include "idt.h"
#include "gdt.h"

#if defined(__linux__)
#error  "You are not using cross-compiler. You use system's compiler!"
#endif

#if !defined(__i386__)
#error "You need to use x86 compiler for the OS model!"
#endif

void maink(void){
    i686_GDT_init();
    i686_IDT_init();
	initWindow();
	print("If you can see this message, then everything that exists works properly!\n");
    
}
