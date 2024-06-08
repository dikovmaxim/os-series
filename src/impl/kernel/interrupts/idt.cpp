#include "idt.hpp"
#include <stdint.h>
#include "../drivers/vga.hpp"

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern "C" void idt_load(idt_ptr_t *idt_ptr) {
    asm volatile("lidt (%0)" : : "r"(idt_ptr));
}

void memset(void *dest, uint8_t val, uint32_t len) {
    uint8_t *dst = (uint8_t *)dest;
    for (; len != 0; len--) {
        *dst++ = val;
    }
}

void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init_idt() {
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = idt_entries;

  idt_set_gate(0, (uint64_t)isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint64_t)isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint64_t)isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint64_t)isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint64_t)isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint64_t)isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint64_t)isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint64_t)isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint64_t)isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint64_t)isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint64_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint64_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint64_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint64_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint64_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint64_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint64_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint64_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint64_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint64_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint64_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint64_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint64_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint64_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint64_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint64_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint64_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint64_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint64_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint64_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint64_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint64_t)isr31, 0x08, 0x8E);

  idt_load(&idt_ptr);

  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_set_gate(32, (uint64_t)irq0, 0x08, 0x8E);
  idt_set_gate(33, (uint64_t)irq1, 0x08, 0x8E);
  idt_set_gate(34, (uint64_t)irq2, 0x08, 0x8E);
  idt_set_gate(35, (uint64_t)irq3, 0x08, 0x8E);
  idt_set_gate(36, (uint64_t)irq4, 0x08, 0x8E);
  idt_set_gate(37, (uint64_t)irq5, 0x08, 0x8E);
  idt_set_gate(38, (uint64_t)irq6, 0x08, 0x8E);
  idt_set_gate(39, (uint64_t)irq7, 0x08, 0x8E);
  idt_set_gate(40, (uint64_t)irq8, 0x08, 0x8E);
  idt_set_gate(41, (uint64_t)irq9, 0x08, 0x8E);
  idt_set_gate(42, (uint64_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (uint64_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (uint64_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (uint64_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (uint64_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (uint64_t)irq15, 0x08, 0x8E);

    idt_load(&idt_ptr);
    asm volatile("sti");

}


void idt_set_gate(int num, uint64_t base, uint16_t sel, uint8_t flags) {
  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_middle = (base>>16) & 0xFFFF;
  idt_entries[num].base_high = (base>>32) & 0xFFFFFFFF;

  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags;
  idt_entries[num].zero = 0;
}

void irq_handler(registers_t regs) {

    printf("received interrupt: %d\n", regs.int_no);

  if (regs.int_no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
}

extern "C" void isr_handler(registers_t regs) {
  printf("received interrupt: %d\n", regs.int_no);
}