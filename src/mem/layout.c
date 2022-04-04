#include "mem/layout.h"

#include <stdint.h>
#include "io/text.h"

#define LAYOUT_PTR ((layout_entry *)0x500)
#define MAX_KERNEL_RESERVED_ADDR 0xfffff
#define MAX_FREE_LAYOUT_ENTRIES 64

typedef struct
{
        uint64_t base;
        uint64_t size;
        uint32_t type;
        uint32_t acpi_attr;
} layout_entry;

typedef enum
{
        LAYOUT_ENTRY_TYPE_NULL = 0,
        LAYOUT_ENTRY_TYPE_FREE = 1,
        LAYOUT_ENTRY_TYPE_RESERVED = 2,
        LAYOUT_ENTRY_TYPE_RECLAIMABLE = 3,
        LAYOUT_ENTRY_TYPE_NON_VOLATILE = 4,
        LAYOUT_ENTRY_TYPE_BAD = 5,
        LAYOUT_ENTRY_TYPE_KERNEL_RESERVED = 6,
} layout_entry_type;

static void
mark_kernel_reserved_layout_entries(void)
{
        layout_entry *lay_ent = LAYOUT_PTR;
        for (; lay_ent->type != LAYOUT_ENTRY_TYPE_NULL; ++lay_ent)
        {
                if (lay_ent->base + lay_ent->size <= MAX_KERNEL_RESERVED_ADDR)
                        lay_ent->type = LAYOUT_ENTRY_TYPE_KERNEL_RESERVED;
        }
}

static const layout_entry *free_lay_ents[MAX_FREE_LAYOUT_ENTRIES];
static int next_free_lay_ent = 0;

static void
save_free_layout_entries(void)
{
        const layout_entry *lay_ent = LAYOUT_PTR;
        for (; lay_ent->type != LAYOUT_ENTRY_TYPE_NULL; ++lay_ent)
        {
                if (lay_ent->type == LAYOUT_ENTRY_TYPE_FREE)
                {
                        free_lay_ents[next_free_lay_ent] = lay_ent;
                        ++next_free_lay_ent;
                }
        }
}

void
init_mem_layout(void)
{
        mark_kernel_reserved_layout_entries();
        save_free_layout_entries();
        log_info("initialized memory layout");
}

uint64_t
find_total_mem_size(void)
{
        const layout_entry *lay_ent = LAYOUT_PTR;
        uint64_t total_size = 0;
        for (; lay_ent->type != LAYOUT_ENTRY_TYPE_NULL; ++lay_ent)
                total_size += lay_ent->size;
        return total_size;
}
