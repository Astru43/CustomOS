#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;
const size_t VGA_COLS = 80;
const size_t VGA_ROWS = 25;

size_t vga_col = 0;
size_t vga_row = 0;
uint8_t vga_color;

inline uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg) {
    return bg << 4 | fg;
}

static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

static inline void vga_shift() {
    for (size_t row = 1; row < VGA_ROWS; row++) {
        for (size_t col = 0; col < VGA_COLS; col++) {
            const size_t index = row * VGA_COLS + col;
            const size_t last_row_index = (row - 1) * VGA_COLS + col;
            vga_buffer[last_row_index] = vga_buffer[index];
            if (row + 1 == VGA_ROWS) {
                vga_buffer[index] = vga_entry(' ', vga_color);
            }
        }
    }
}

void vga_init() {
    vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    for (size_t row = 0; row < VGA_ROWS; row++) {
        for (size_t col = 0; col < VGA_COLS; col++) {
            const size_t index = row * VGA_COLS + col;
            vga_buffer[index] = vga_entry(' ', vga_color);
        }
    }
}

void vga_putc(char c) {
    switch (c) {
    case '\n':
        vga_col = 0;
        vga_row++;
        break;
    default:
        const size_t index = VGA_COLS * vga_row + vga_col;
        vga_buffer[index] = vga_entry(c, vga_color);
        vga_col++;
        break;
    }
    if (vga_col >= VGA_COLS) {
        vga_col = 0;
        vga_row++;
    }
    if (vga_row >= VGA_ROWS) {
        vga_col = 0;
        vga_row--;
        vga_shift();
    }
}

void vga_print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        vga_putc(str[i]);
}

void vga_setcolor(uint8_t color) { vga_color = color; }

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char *str, size_t lenght) {
    int str_start = 0;
    int str_end = lenght - 1;
    while (str_start < str_end) {
        swap((str + str_start), (str + str_end));
        str_start++;
        str_end--;
    }
}

void itoa(int num, char *buffer, size_t *buf_size, int base) {
    int i = 0;
    if (*buf_size == 0) {
        i++;
        if (num < 0)
            i++;
        while (num != 0) {
            num /= base;
            i++;
        }
        *buf_size = i;
        return;
    } else {
        bool negative = false;
        if (num < 0)
            negative = true;

        if (num == 0 && base == 10) {
            buffer[i++] = '0';
            buffer[i++] = '\0';
            return;
        }

        while (num != 0) {
            int rem = num % base;
            buffer[i++] = rem <= 9 ? rem + '0' : (rem - 10) + 'A';
            num /= base;
        }

        if (negative)
            buffer[i++] = '-';

        buffer[i] = '\0';
        reverse(buffer, i);
        return;
    }
}