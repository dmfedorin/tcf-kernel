#ifndef IDT_H_aYna97pe01d37OTELsmr8fWVZcwBh67r
#define IDT_H_aYna97pe01d37OTELsmr8fWVZcwBh67r

#include "isr.h"

void
init_idt_default(void);

void
load_idt(void);

typedef enum
{
        IDT_ENTRY_DIV_BY_0 = 0x0,
        IDT_ENTRY_DEBUG = 0x1,
        IDT_ENTRY_PAGE_FAULT = 0xe,
} idt_entry;

typedef enum
{
        INT_DESC_GATE_TYPE_INT = 0x8e,
        INT_DESC_GATE_TYPE_TRAP = 0x8f,
} int_desc_gate_type;

void
set_idt_entry(idt_entry ent, int_desc_gate_type gate_type,
              void (*isr)(const int_frame *frame));

#endif
