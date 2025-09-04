#include <stddef.h>
#include <stdint.h>
#include "kernel.h"

#if defined(__linux__)
#error  "You are not using cross-compiler. You use system's compiler!"
#endif

#if !defined(__i386__)
#error "You need to use x86 compiler for the OS model!"
#endif



size_t strlen(const char *str){
  size_t len = 0;
  while(str[len] != '\0')
    len++;
  return len;
}

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
uint16_t* VGA_MEM = (uint16_t*)0xB8000;

size_t row;
size_t col;
uint8_t term_color;

void terminal_init(void){
  row = 0;
  col = 0;
  term_color = vga_entry_color(COLOR_LIGHT_GRAY, COLOR_BLACK);
  for(size_t y = 0; y < VGA_HEIGHT; y++){
    for(size_t x = 0; x < VGA_WIDTH; x++){
      const size_t idx = y * VGA_WIDTH + x;
      VGA_MEM[idx] = vga_entry(' ', term_color);
    }
  }
}

void terminal_setcolor(uint8_t color){
  term_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y){
  const size_t idx = y * VGA_WIDTH + x;
  VGA_MEM[idx] = vga_entry(c, color);
}

void terminal_putchar(char c){
  terminal_putentryat(c, term_color, col, row);
  if(++col == VGA_WIDTH){
    col = 0;
    if(++row == VGA_HEIGHT)
      row = 0;
  }
}

void terminal_write(const char *data, size_t size){
  for(size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_printstr(const char *data){
  terminal_write(data, strlen(data));
}

void maink(void){
  terminal_init();
  terminal_printstr("Hello World!\n");
}
