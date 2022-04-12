#ifndef CPU_H_JgTolb0oBuaKJT1CbUDkkUQnKkpt0p5J
#define CPU_H_JgTolb0oBuaKJT1CbUDkkUQnKkpt0p5J

#include <stdint.h>

typedef struct
{
        uint64_t rax;
        uint64_t rbx;
        uint64_t rcx;
        uint64_t rdx;
        uint64_t rsp;
        uint64_t rbp;
        uint64_t rsi;
        uint64_t rdi;
} cpu_regs;

typedef struct
{
        cpu_regs regs;
} cpu_state;

cpu_state
get_cpu_state(void);

void
print_cpu_state(const cpu_state *state);

#endif
