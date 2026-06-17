#include <stdint.h>
#include <stddef.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;


size_t terminal_row = 0;
size_t terminal_column = 0;

uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
        return;
    }
    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    
    vga_buffer[index] = vga_entry(c, 0x0F);

    terminal_column++;

    if (terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    }
}

void terminal_print(const char* data) {
    for (size_t i = 0; data[i] != '\0'; i++) {
        terminal_putchar(data[i]);
    }
}
