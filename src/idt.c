#include "idt.h"
#include "memory.h"

IDTEntry idt_entry[256];
IDTptr idt_ptr;

extern void idt_flush(uint32_t);
/*
void initIDT(){
    for(int i=0; i< 256;i++){
        setIDTGate(i, (uint32_t)defaultISR,0x08, 0x8E);
    }

    idt_ptr.limit = (sizeof(IDTEntry) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt_entry;
    idt_flush(&idt_ptr);
    
}
*/

void initIDT(){
    idt_ptr.limit = sizeof(IDTEntry) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entry;

    memset(&idt_entry, 0, sizeof(IDTEntry) * 256);
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

    setIDTGate(0, (uint32_t)isr0, IDT_SEL, IDT_FLAG);
    setIDTGate(1, (uint32_t)isr1, IDT_SEL, IDT_FLAG);
    setIDTGate(2, (uint32_t)isr2, IDT_SEL, IDT_FLAG);
    setIDTGate(3, (uint32_t)isr3, IDT_SEL, IDT_FLAG);
    setIDTGate(4, (uint32_t)isr4, IDT_SEL, IDT_FLAG);
    setIDTGate(5, (uint32_t)isr5, IDT_SEL, IDT_FLAG);
    setIDTGate(6, (uint32_t)isr6, IDT_SEL, IDT_FLAG);
    setIDTGate(7, (uint32_t)isr7, IDT_SEL, IDT_FLAG);
    setIDTGate(8, (uint32_t)isr8, IDT_SEL, IDT_FLAG);
    setIDTGate(9, (uint32_t)isr9, IDT_SEL, IDT_FLAG);
    setIDTGate(10, (uint32_t)isr10, IDT_SEL, IDT_FLAG);
    setIDTGate(11, (uint32_t)isr11, IDT_SEL, IDT_FLAG);
    setIDTGate(12, (uint32_t)isr12, IDT_SEL, IDT_FLAG);
    setIDTGate(13, (uint32_t)isr13, IDT_SEL, IDT_FLAG);
    setIDTGate(14, (uint32_t)isr14, IDT_SEL, IDT_FLAG);
    setIDTGate(15, (uint32_t)isr15, IDT_SEL, IDT_FLAG);
    setIDTGate(16, (uint32_t)isr16, IDT_SEL, IDT_FLAG);
    setIDTGate(17, (uint32_t)isr17, IDT_SEL, IDT_FLAG);
    setIDTGate(18, (uint32_t)isr18, IDT_SEL, IDT_FLAG);
    setIDTGate(19, (uint32_t)isr19, IDT_SEL, IDT_FLAG);
    setIDTGate(20, (uint32_t)isr20, IDT_SEL, IDT_FLAG);
    setIDTGate(21, (uint32_t)isr21, IDT_SEL, IDT_FLAG);
    setIDTGate(22, (uint32_t)isr22, IDT_SEL, IDT_FLAG);
    setIDTGate(23, (uint32_t)isr23, IDT_SEL, IDT_FLAG);
    setIDTGate(24, (uint32_t)isr24, IDT_SEL, IDT_FLAG);
    setIDTGate(25, (uint32_t)isr25, IDT_SEL, IDT_FLAG);
    setIDTGate(26, (uint32_t)isr26, IDT_SEL, IDT_FLAG);
    setIDTGate(27, (uint32_t)isr27, IDT_SEL, IDT_FLAG);
    setIDTGate(28, (uint32_t)isr28, IDT_SEL, IDT_FLAG);
    setIDTGate(29, (uint32_t)isr29, IDT_SEL, IDT_FLAG);
    setIDTGate(30, (uint32_t)isr30, IDT_SEL, IDT_FLAG);
    setIDTGate(31, (uint32_t)isr31, IDT_SEL, IDT_FLAG);

    setIDTGate(32, (uint32_t)irq0, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq1, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq2, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq3, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq4, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq5, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq6, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq7, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq8, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq9, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq10, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq11, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq12, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq13, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq14, IDT_SEL, IDT_FLAG);
    setIDTGate(32, (uint32_t)irq15, IDT_SEL, IDT_FLAG);
    
    // idt for syscalls
    setIDTGate(128, (uint32_t)isr128, IDT_SEL, IDT_FLAG);
    setIDTGate(177, (uint32_t)isr177, IDT_SEL, IDT_FLAG);
    idt_flush((uint32_t)&idt_entry);
}


void setIDTGate(uint32_t num, uint32_t handler, uint16_t selector, uint8_t flags){
       idt_entry[num].offsetLow = handler & 0xFFFF;
       idt_entry[num].segmentSel = selector;
       idt_entry[num].reserved = 0;
       idt_entry[num].flags = flags | 0x60;
       idt_entry[num].offsetHigh = (handler >> 16) & 0xFFFF;
}

char* exception_msg[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out Of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not Present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment fault",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(INTREG* regs){
    if(regs->int_no < 32){
        print(exception_msg[regs->int_no]);
        print("\n");
        print("Exception! System halted!\n");
        for(;;);
        }
}

void* irq_routines[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void irq_install_handler(int irq, void (*handler)(INTREG *r)){
    irq_routines[irq] = handler;    
}

void irq_uninstall_handler(int irq){
    irq_routines[irq] = 0;    
}

void irq_handler(INTREG *regs){
    void (*handler)(INTREG* regs);

    handler = irq_routines[regs->int_no - 32];

    if(handler)
        handler(regs);

    if(regs->int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}
