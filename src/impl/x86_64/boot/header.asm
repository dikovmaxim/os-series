section .multiboot_header
header_start:
    ; magic number
    dd 0xe85250d6             ; Multiboot2 magic number
    ; architecture
    dd 0                      ; Protected mode i386
    ; header length
    dd header_end - header_start
    ; checksum
    dd -(0xe85250d6 + 0 + (header_end - header_start))

    ; End tag
    dw 0
    dw 0
    dd 8
header_end:
