#ifndef PORT_H_ogLcj36c3GU07Cx3WlIreSC355OCboFx
#define PORT_H_ogLcj36c3GU07Cx3WlIreSC355OCboFx

#include <stdint.h>

typedef enum
{
        PORT_PIC1_CTRL = 0x20,
        PORT_PIC1_DATA = 0x21,
        PORT_PS2_DATA = 0x60,
        PORT_PS2_CTRL = 0x64,
        PORT_PIC2_CTRL = 0xa0,
        PORT_PIC2_DATA = 0xa1,
        PORT_VGA_CTRL = 0x3d4,
        PORT_VGA_DATA = 0x3d5,
} port;

void
write_port_byte(port p, uint8_t data);

uint8_t
read_port_byte(port p);

void
write_port_word(port p, uint16_t data);

uint16_t
read_port_word(port p);

void
write_port_long(port p, uint32_t data);

uint32_t
read_port_long(port p);

#endif
