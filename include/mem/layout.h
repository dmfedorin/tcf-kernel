#ifndef LAYOUT_H_dGNV6j3IBsXhY3P7hMBIqMrCaR4Pwz9H
#define LAYOUT_H_dGNV6j3IBsXhY3P7hMBIqMrCaR4Pwz9H

#define MAX_KERNEL_RESERVED_ADDR 0xfffff

#include <stdint.h>

void
init_mem_layout(void);

uint64_t
total_mem_layout_size(void);

typedef struct
{
        uint64_t base;
        uint64_t size;
        uint32_t type;
        uint32_t acpi_attr;
} layout_entry;

const layout_entry **
free_mem_layout_entries(void);

int
free_mem_layout_entry_count(void);

#endif
