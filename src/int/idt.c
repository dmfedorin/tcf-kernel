#include "int/idt.h"

#include <stdint.h>
#include "util/debug.h"
#include "defs.h"
#include "int/isr.h"

#define IDT_SIZE 256
#define IDT_PTR ((int_desc *)0x70000)

typedef struct __attribute__((packed))
{
        uint16_t offset_0;
        uint16_t selector;
        uint8_t ist;
        uint8_t type_attr;
        uint16_t offset_1;
        uint32_t offset_2;
        uint32_t _zero;
} int_desc;

static inline uint16_t
int_desc_offset_0(void (*isr)(const int_frame *frame))
{
        return (uintptr_t)isr & 0xffff;
}

static inline uint16_t
int_desc_offset_1(void (*isr)(const int_frame *frame))
{
        return ((uintptr_t)isr & 0xffff0000) >> 16;
}

static inline uint32_t
int_desc_offset_2(void (*isr)(const int_frame *frame))
{
        return ((uintptr_t)isr & 0xffffffff00000000) >> 32;
}

void
init_idt_default(void)
{
        for (int i = 0; i < IDT_SIZE; ++i)
        {
                IDT_PTR[i] = (int_desc)
                {
                        .offset_0 = int_desc_offset_0(default_isr),
                        .offset_1 = int_desc_offset_1(default_isr),
                        .offset_2 = int_desc_offset_2(default_isr),
                        .selector = KERNEL_CODE_SEL,
                        .type_attr = INT_DESC_GATE_TYPE_INT,
                        .ist = 0,
                        ._zero = 0,
                };
        }
        log_info("initialized idt with default isr");
}

typedef struct __attribute__((packed))
{
        uint16_t size;
        uint64_t offset;
} idtr;

void
load_idt(void)
{
        idtr idtr =
        {
                .offset = (uintptr_t)IDT_PTR,
                .size = sizeof(int_desc) * IDT_SIZE - 1,
        };
        __asm__("lidt %0\n"
                :
                : "m" (idtr));
        log_info("loaded idt");
}

void
set_idt_entry(idt_entry ent, int_desc_gate_type gate_type,
              void (*isr)(const int_frame *frame))
{
        IDT_PTR[ent].offset_0 = int_desc_offset_0(isr);
        IDT_PTR[ent].offset_1 = int_desc_offset_1(isr);
        IDT_PTR[ent].offset_2 = int_desc_offset_2(isr);
        IDT_PTR[ent].type_attr = gate_type;
}
