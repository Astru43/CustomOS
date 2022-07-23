#pragma once

enum VGA_COLOR {
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE,
};

uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg);

void vga_init();
void vga_putc(char c);
void vga_print(const char *str);
void vga_setcolor(uint8_t color);

void swap(char *a, char *b);
void reverse(char* str, size_t length);
void itoa(int num, char* buffer, size_t *buf_size, int base);