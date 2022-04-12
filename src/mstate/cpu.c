#include "mstate/cpu.h"

#include "io/text.h"

static cpu_regs
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

cpu_state
get_cpu_state(void)
{
        return (cpu_state)
        {
                .regs = get_cpu_regs(),
        };
}

static void
print_cpu_regs(const cpu_regs *regs)
{
        put_str("cpu registers:\n");
        put_str("rax: ");
        put_hex(&regs->rax, sizeof(uint64_t));
        put_char(' ');
        put_str("rbx: ");
        put_hex(&regs->rbx, sizeof(uint64_t));
        put_char(' ');
        put_str("rcx: ");
        put_hex(&regs->rcx, sizeof(uint64_t));
        put_char('\n');
        put_str("rdx: ");
        put_hex(&regs->rdx, sizeof(uint64_t));
        put_char(' ');
        put_str("rsp: ");
        put_hex(&regs->rsp, sizeof(uint64_t));
        put_char(' ');
        put_str("rbp: ");
        put_hex(&regs->rbp, sizeof(uint64_t));
        put_char('\n');
        put_str("rsi: ");
        put_hex(&regs->rsi, sizeof(uint64_t));
        put_char(' ');
        put_str("rdi: ");
        put_hex(&regs->rdi, sizeof(uint64_t));
        put_char('\n');
}

void
print_cpu_state(const cpu_state *state)
{
        print_cpu_regs(&state->regs);
}
