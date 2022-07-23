#include <stddef.h>
#include <stdint.h>

#include "vga.h"

void kernel_main() {
    vga_init();
    vga_print("Hello world\n");
    vga_print("Print works\n");

    char buffer[5];
    size_t buf_size = 5;

    for (size_t i = 0; i < 25; i++) {
        itoa(i, buffer, &buf_size, 16);
        vga_print("Line ");
        vga_print(buffer);
        vga_print("\n");
    }
}
