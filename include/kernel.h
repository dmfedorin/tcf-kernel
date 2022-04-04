#ifndef KERNEL_H_x8ipKUjqJtEpqUFmNH0PMfhrMOuUAHm7
#define KERNEL_H_x8ipKUjqJtEpqUFmNH0PMfhrMOuUAHm7

#include <stdint.h>

typedef struct
{
        uint64_t rax, rbx, rcx, rdx, rsp, rbp, rsi, rdi;
} cpu_regs;

cpu_regs
get_cpu_regs(void);

void
init_kernel(void);

#endif
