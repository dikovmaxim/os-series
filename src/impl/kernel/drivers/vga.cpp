#include "vga.hpp"
#include <stdarg.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static void put_char(char c) {
    if (c == '\n') {
        line++;
        pos = 0;
    } else {
        video_memory[(line * VGA_WIDTH + pos) * 2] = c;
        video_memory[(line * VGA_WIDTH + pos) * 2 + 1] = 0x07; // White on black
        pos++;
        if (pos >= VGA_WIDTH) {
            pos = 0;
            line++;
        }
    }

    if (line >= VGA_HEIGHT) {
        // Scroll the screen up by one line
        for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i++) {
            video_memory[i] = video_memory[i + VGA_WIDTH * 2];
        }
        for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i < VGA_HEIGHT * VGA_WIDTH * 2; i += 2) {
            video_memory[i] = ' ';
            video_memory[i + 1] = 0x07;
        }
        line = VGA_HEIGHT - 1;
    }
}

static void print_decimal(int value) {
    if (value < 0) {
        put_char('-');
        value = -value;
    }
    if (value == 0) {
        put_char('0');
        return;
    }

    char buffer[10];
    int index = 0;

    while (value > 0) {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    }

    for (int i = index - 1; i >= 0; i--) {
        put_char(buffer[i]);
    }
}

static void print_unsigned(unsigned int value) {
    if (value == 0) {
        put_char('0');
        return;
    }

    char buffer[10];
    int index = 0;

    while (value > 0) {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    }

    for (int i = index - 1; i >= 0; i--) {
        put_char(buffer[i]);
    }
}

static void print_hex(unsigned int value) {
    const char* hex_digits = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        put_char(hex_digits[(value >> i) & 0xF]);
    }
}

static void print_string(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            switch (format[i]) {
                case 'd':
                    print_decimal(va_arg(args, int));
                    break;
                case 'u':
                    print_unsigned(va_arg(args, unsigned int));
                    break;
                case 'x':
                    print_hex(va_arg(args, unsigned int));
                    break;
                case 'c':
                    put_char((char)va_arg(args, int));
                    break;
                case 's':
                    print_string(va_arg(args, char*));
                    break;
                case 'p':
                    print_hex(va_arg(args, unsigned int));
                    break;
                default:
                    put_char(format[i]);
                    break;
            }
        } else if (format[i] == '\n') {
            put_char('\n');
        } else {
            put_char(format[i]);
        }
    }

    va_end(args);
}
