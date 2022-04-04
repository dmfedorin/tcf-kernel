#include "int/isr.h"

#include "io/text.h"
#include "io/port.h"
#include "int/pic.h"

__attribute__((interrupt)) void
default_isr(const int_frame *frame)
{
}

__attribute__((interrupt)) void
div_by_0_isr(const int_frame *frame)
{
}

__attribute__((interrupt)) void
debug_isr(const int_frame *frame)
{
        log_info("debug isr called");
}

__attribute__((interrupt)) void
keyboard_isr(const int_frame *frame)
{
        uint8_t scancode = read_port_byte(PORT_PS2_DATA);
        end_pic1_int();
}
