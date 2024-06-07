#include <stdint.h>
#include <stdbool.h>

#include "drivers/vga.hpp"
#include "multiboot.h"

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


extern "C" void kernel_main(uint32_t multiboot_magic, multiboot_info_t* mbi) {
    // Check if the magic number is valid for Multiboot 1
    if (multiboot_magic != 0x2BADB002) {
        printf("Invalid multiboot magic number\n");
        while (1) { asm("hlt"); }
    }else{
        printf("Multiboot magic number is valid\n");
    }

    // You can add more processing code here to handle the `mbi` if needed

    while (1) {
        asm("hlt");
    }
}