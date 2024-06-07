#include <stdint.h>
#include <stdbool.h>

#include "multiboot.h"

#define VIDEO_MEMORY (char*) 0xb8000
static int line = 0;

// Function to print to the screen
void printf(const char* str) {
    char* video_memory = VIDEO_MEMORY;
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[line * 80 * 2 + i * 2] = str[i];
        video_memory[line * 80 * 2 + i * 2 + 1] = 0x0f;
    }
    line++;
}

// Function to get CR0
uint64_t get_cr0() {
    uint64_t cr0;
    __asm__ __volatile__("mov %%cr0, %0" : "=r" (cr0));
    return cr0;
}

// Function to get CS register
uint64_t get_cs() {
    uint16_t cs;
    __asm__ __volatile__("mov %%cs, %0" : "=r" (cs));
    return cs;
}

// Function to get CR4 register
uint64_t get_cr4() {
    uint64_t cr4;
    __asm__ __volatile__("mov %%cr4, %0" : "=r" (cr4));
    return cr4;
}

// Function to check if 64-bit mode is enabled
bool is_64bit_mode_enabled() {
    uint64_t cs = get_cs();
    return (cs & 0x3) == 0;  // In 64-bit mode, CS should be pointing to a 64-bit code segment (typically 0x10 or 0x8)
}

// Function to check if GDT is enabled
bool is_gdt_enabled() {
    uint64_t cr0 = get_cr0();
    uint64_t cr4 = get_cr4();
    return (cr0 & (1 << 0)) && (cr4 & (1 << 5));  // Protected mode and PAE (Page Address Extension) enabled
}

// Kernel main function
extern "C" void kernel_main(multiboot_info_t* mbd) {


    printf("Hello from 64-bit mode!");

    if (is_64bit_mode_enabled()) {
        printf("System is running in 64-bit mode");
    } else {
        printf("System is running in 32-bit mode");
    }

    if (is_gdt_enabled()) {
        printf("GDT is enabled");
    } else {
        printf("GDT is disabled");
    }

    while (1);
}
