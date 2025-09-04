#ifndef VGA_H
#define VGA_H

#include "kernel.h"

typedef enum {
  COLOR_BLACK,
  COLOR_BLUE,
  COLOR_GREEN,
  COLOR_CYAN,
  COLOR_RED,
  COLOR_MAGENTA,
  COLOR_BROWN,
  COLOR_LIGHT_GRAY,
  COLOR_DARK_GRAY,
  COLOR_LIGHT_BLUE,
  COLOR_LIGHT_GREEN,
  COLOR_LIGHT_CYAN,
  COLOR_LIGHT_RED,
  COLOR_LIGHT_MAGENTA,
  COLOR_LIGHT_BROWN,
  COLOR_WHITE
} VGA_COLOR;

static inline uint8_t vga_entry_color(VGA_COLOR fg, VGA_COLOR bg){
  return fg | bg << 4;
}
static inline uint16_t vga_entry(unsigned char c, uint8_t color){
  return (uint16_t)c | (uint16_t)color << 8;
}

size_t strlen(const char *str);
void initWindow(void);
void printChar(unsigned char c);
void print(const char *data);
#endif
