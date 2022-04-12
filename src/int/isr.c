#include "int/isr.h"

#include "util/debug.h"
#include "kernel.h"

__attribute__((interrupt)) void
default_isr(const int_frame *frame)
{
        log_warning("default isr called, please write a proper handler");
}

__attribute__((interrupt)) void
debug_isr(const int_frame *frame)
{
        log_info("debug isr called");
}

__attribute__((interrupt)) void
page_fault_isr(const int_frame *frame)
{
        log_warning("page fault");
}
