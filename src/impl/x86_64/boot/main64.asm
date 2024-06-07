global long_mode_start
extern kernel_main

section .text
bits 64

long_mode_start:
    ; Load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Set up stack (optional, stack setup can be done here if needed)
    ; mov rsp, <desired stack address>

    ; Call kernel_main with multiboot magic and mbi pointer
    mov rdi, 0x2BADB002    ; Multiboot 1 magic number
    mov rsi, [rbx + 8]      ; Multiboot information structure pointer
    call kernel_main

    hlt
