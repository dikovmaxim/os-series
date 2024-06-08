
#include <stdint.h>

struct idt_entry {
  uint16_t base_low;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_middle;
  uint32_t base_high;
  uint32_t zero;
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr {
  uint16_t limit;
  idt_entry_t *base;
}__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

extern "C" void idt_load(idt_ptr_t *idt_ptr);
void init_idt();
void idt_set_gate(int, uint64_t, uint16_t, uint8_t);

typedef struct registers {
  uint64_t ds;
  uint64_t rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi;
  uint64_t int_no, err_code;
  uint64_t rip, cs, eflags, userrsp, ss;

} registers_t;

extern "C" void isr_handler(registers_t regs);
extern "C" void irq_handler(registers_t regs);

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();