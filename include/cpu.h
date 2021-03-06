#ifndef __CPU_H__
# define __CPU_H__

struct nes;

enum interrupt_type {
    INTERRUPT_TYPE_NMI,
    INTERRUPT_TYPE_RST,
    INTERRUPT_TYPE_BRK
};

struct cpu
{
    uint8_t     mem[0x10000];

    struct {
        uint8_t a;

        uint8_t x;
        uint8_t y;

        uint8_t s;

        union {
            struct {
                unsigned short  c       :1; // carry
                unsigned short  z       :1; // zero
                unsigned short  i       :1; // IRQ disabled
                unsigned short  d       :1; // Decimal mode
                unsigned short  b       :1; // Interrupt caused by brk
                unsigned short  _u      :1; // Unused
                unsigned short  v       :1; // Oveflow
                unsigned short  n       :1; // Negative
            };
            uint8_t p;
        };

        uint16_t        pc;
        uint16_t        new_pc;
    } regs;

    struct {
        int32_t         run;
        uint32_t        count;
    } debug;

    struct nes *        nes;
};

void cpu_init (struct cpu *, struct nes *);
int cpu_disassemble (struct cpu *);
int cpu_exec (struct cpu *);
int cpu_call (struct cpu *, uint8_t, uint16_t);
void cpu_interrupt (struct cpu *, enum interrupt_type);

#endif /* !__CPU_H__ */
