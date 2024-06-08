#include <stdint.h>
#include <stdbool.h>

#include "drivers/vga.hpp"
#include "multiboot.h"
#include "interrupts/idt.hpp"

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


#define PAGE_SIZE 4096  // Assuming 4KB pages


extern "C" void kernel_main(uint32_t multiboot_magic, multiboot_info* mbi) {
    // Check if the magic number is valid for Multiboot 1
    if (multiboot_magic != 0x2BADB002) {
        printf("Invalid multiboot magic number\n");
        while (1) { asm("hlt"); }
    } else {
        printf("Multiboot magic number is valid\n");
    }

    if (is_64bit_mode_enabled()) {
        printf("64-bit mode is enabled\n");
    } else {
        printf("64-bit mode is not enabled\n");
        while (1) { asm("hlt"); }
    }

    if (is_gdt_enabled()) {
        printf("GDT is enabled\n");
    } else {
        printf("GDT is not enabled\n");
        while (1) { asm("hlt"); }
    }

    // Check if the memory map is available
    if (!(mbi->flags & 0x40)) {
        printf("Memory map is not available\n");
        while (1) { asm("hlt"); }
    } else {
        printf("Memory map is available\n");
    }

    //check if interrupts are enabled
    uint64_t rflags;
    __asm__ __volatile__("pushf; pop %0" : "=rm" (rflags));
    if (rflags & (1 << 9)) {
        printf("Interrupts are enabled\n");
    } else {
        printf("Interrupts are not enabled\n");
    }


    printf("CR0 = 0x%x\n", get_cr0());
    printf("CS = 0x%x\n", get_cs());
    printf("CR4 = 0x%x\n", get_cr4());



    printf("Memory map length = %u, memory map address = 0x%x\n", mbi->mmap_length, mbi->mmap_addr);


    init_idt();

    //check if interrupts are enabled
    __asm__ __volatile__("pushf; pop %0" : "=rm" (rflags));
    if (rflags & (1 << 9)) {
        printf("Interrupts are enabled\n");
    } else {
        printf("Interrupts are not enabled\n");
    }
    

    while (1) {
        asm("hlt");
    }
}