#include "kernel.h"
#include "vga.h"

size_t strlen(const char *str){
  size_t len = 0;
  while(str[len] != '\0')
    len++;
  return len;
}

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
uint16_t* VGA_MEM = (uint16_t*)0xB8000;

size_t term_row;
size_t term_col;
uint8_t term_color;

void initWindow(void){
  term_row = 0;
  term_col = 0;
  term_color = vga_entry_color(COLOR_LIGHT_GRAY, COLOR_BLACK);
  for(size_t y = 0; y < VGA_HEIGHT; y++){
    for(size_t x = 0; x < VGA_WIDTH; x++){
      const size_t idx = y * VGA_WIDTH + x;
      VGA_MEM[idx] = vga_entry(' ', term_color);
    }
  }
}

void printChar(unsigned char c){
    if(c == '\n'){
        term_col = 0;
        if(++term_row >= VGA_HEIGHT)
            term_row = 0;
        return;
    }
   
    // First method for '\t'
    if(c == '\t'){
        term_col = (term_col + 8) & ~7;
        if(++term_col >= VGA_WIDTH){
            if(++term_row == VGA_HEIGHT)
              term_row = 0;
        }
        return;
    }

    // Second method for '\t'
    const int idx = term_row * VGA_WIDTH + term_col;
    VGA_MEM[idx] = vga_entry(c, term_color);
    if(++term_col == VGA_WIDTH){
        term_col = 0;
        if(++term_row == VGA_HEIGHT)
            term_row = 0;
    }
    
}
void print(const char *data){
    for(size_t i=0;i<strlen(data);i++){
        printChar(data[i]);
    }
}
