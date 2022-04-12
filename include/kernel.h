#ifndef KERNEL_H_x8ipKUjqJtEpqUFmNH0PMfhrMOuUAHm7
#define KERNEL_H_x8ipKUjqJtEpqUFmNH0PMfhrMOuUAHm7

void
init_kernel(void);

void
hang(void);

typedef enum
{
        PANIC_CODE_TEST,
        PANIC_CODE_GENERAL,
} panic_code;

void
panic(panic_code code);

#endif
