#ifndef ISR_H_vyKdF1vXsY02XygexJ9YJYT3IuoNv2KY
#define ISR_H_vyKdF1vXsY02XygexJ9YJYT3IuoNv2KY

#include <stdint.h>

typedef struct
{
        uint64_t rip, cs, flags, rsp, ss;
} int_frame;

__attribute__((interrupt)) void
default_isr(const int_frame *frame);

__attribute__((interrupt)) void
div_by_0_isr(const int_frame *frame);

__attribute__((interrupt)) void
debug_isr(const int_frame *frame);

__attribute__((interrupt)) void
keyboard_isr(const int_frame *frame);

#endif
