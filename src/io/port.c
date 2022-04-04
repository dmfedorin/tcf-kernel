#include "io/port.h"

/* io port operations are slow, it is wise to wait on them to finish */
static inline void
wait_port_io(void)
{
        __asm__("outl %0, $0x80\n"
                :
                : "a" (0));
}

void
write_port_byte(port p, uint8_t data)
{
        __asm__("outb %0, %1\n"
                :
                : "a" (data), "Nd" (p));
        wait_port_io();
}

uint8_t
read_port_byte(port p)
{
        uint8_t res;
        __asm__("inb %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        wait_port_io();
        return res;
}

void
write_port_word(port p, uint16_t data)
{
        __asm__("outw %0, %1\n"
                :
                : "a" (data), "Nd" (p));
        wait_port_io();
}

uint16_t
read_port_word(port p)
{
        uint16_t res;
        __asm__("inw %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        wait_port_io();
        return res;
}

void
write_port_long(port p, uint32_t data)
{
        __asm__("outl %0, %1\n"
                :
                : "a" (data), "Nd" (p));
        wait_port_io();
}

uint32_t
read_port_long(port p)
{
        uint32_t res;
        __asm__("inl %1, %0\n"
                : "=a" (res)
                : "Nd" (p));
        wait_port_io();
        return res;
}
