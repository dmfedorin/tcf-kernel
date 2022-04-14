#include "mem/layout.h"

#include <stdint.h>
#include "util/debug.h"

#define LAYOUT_PTR ((layout_entry *)0x500)
#define MAX_FREE_LAYOUT_ENTRIES 64

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
static int free_lay_ent_cnt = 0;

static void
save_free_layout_entries(void)
{
        const layout_entry *lay_ent = LAYOUT_PTR;
        for (; lay_ent->type != LAYOUT_ENTRY_TYPE_NULL; ++lay_ent)
        {
                if (lay_ent->type == LAYOUT_ENTRY_TYPE_FREE)
                {
                        free_lay_ents[free_lay_ent_cnt] = lay_ent;
                        ++free_lay_ent_cnt;
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

size_t
total_mem_layout_size(void)
{
        const layout_entry *lay_ent = LAYOUT_PTR;
        size_t total_size = 0;
        for (; lay_ent->type != LAYOUT_ENTRY_TYPE_NULL; ++lay_ent)
                total_size += lay_ent->size;
        return total_size;
}

const layout_entry **
free_mem_layout_entries(void)
{
        return free_lay_ents;
}

int
free_mem_layout_entry_count(void)
{
        return free_lay_ent_cnt;
}
