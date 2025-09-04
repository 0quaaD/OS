#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "vga.h"

#if defined(__linux__)
#error  "You are not using cross-compiler. You use system's compiler!"
#endif

#if !defined(__i386__)
#error "You need to use x86 compiler for the OS model!"
#endif

void maink(void){
    initWindow();
    print("1st message without any escape chars.");
    print("2nd message with \nnewline.\n");
    print("3rd message with \ttab.\n");
}
