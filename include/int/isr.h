#ifndef ISR_H_vyKdF1vXsY02XygexJ9YJYT3IuoNv2KY
#define ISR_H_vyKdF1vXsY02XygexJ9YJYT3IuoNv2KY

#include <stdint.h>

typedef struct int_frame int_frame;

__attribute__((interrupt)) void
default_isr(const int_frame *frame);

__attribute__((interrupt)) void
debug_isr(const int_frame *frame);

__attribute__((interrupt)) void
page_fault_isr(const int_frame *frame);

#endif
