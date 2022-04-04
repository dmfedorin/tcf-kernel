#include "kernel.h"

#include "mem/layout.h"
#include "io/text.h"

cpu_regs
get_cpu_regs(void)
{
        cpu_regs regs;
        __asm__("mov %%rax, %0\n"
                "mov %%rbx, %1\n"
                "mov %%rcx, %2\n"
                "mov %%rdx, %3\n"
                "mov %%rsp, %4\n"
                "mov %%rbp, %5\n"
                "mov %%rsi, %6\n"
                "mov %%rdi, %7\n"
                : "=m" (regs.rax), "=m" (regs.rbx), "=m" (regs.rcx),
                  "=m" (regs.rdx), "=m" (regs.rsp), "=m" (regs.rbp),
                  "=m" (regs.rsi), "=m" (regs.rdi));
        return regs;
}

void
init_kernel(void)
{
        init_mem_layout();
        log_info("initialized kernel");
}
