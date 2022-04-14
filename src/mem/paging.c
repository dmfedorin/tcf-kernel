#include "mem/paging.h"

#include "util/debug.h"
#include <stdint.h>
#include <stdbool.h>
#include "mem/pagealloc.h"
#include "libc/string.h"
#include "mem/layout.h"
#include "io/text.h"

#define MAX_TABLE_ENTRIES 512

typedef struct
{
        int pdpt;
        int pdt;
        int pt;
        int page;
} page_index;

static void
print_page_index(const page_index *ind)
{
        put_str("pdpt: ");
        put_hex(&ind->pdpt, sizeof(int));
        put_char('\n');
        put_str("pdt: ");
        put_hex(&ind->pdt, sizeof(int));
        put_char('\n');
        put_str("pt: ");
        put_hex(&ind->pt, sizeof(int));
        put_char('\n');
        put_str("page: ");
        put_hex(&ind->page, sizeof(int));
        put_char('\n');
}

static page_index
index_virtual_addr(const void *addr)
{
        return (page_index)
        {
                .page = (uintptr_t)addr >> 12 & 0x1ff,
                .pt = (uintptr_t)addr >> 21 & 0x1ff,
                .pdt = (uintptr_t)addr >> 30 & 0x1ff,
                .pdpt = (uintptr_t)addr >> 39 & 0x1ff,
        };
}

/* structure also works for pdpt entry and pml4 entry */
typedef struct
{
        bool present : 1;
        bool read_write : 1;
        bool user_super : 1;
        bool write_through : 1;
        bool disable_caching : 1;
        bool accessed : 1;
        bool available_0 : 1;
        bool large_pages : 1;
        uint8_t available_1 : 4;
        uint64_t addr : 52;
} page_dir_entry;

/* structure also works for pdpt and pml4 */
typedef struct
{
        page_dir_entry entries[MAX_TABLE_ENTRIES];
} page_dir;

static page_dir *pml4;

void
init_paging(void)
{
        pml4 = free_zero_page();
        log_info("initialized paging");
}

typedef struct
{
        bool present : 1;
        bool read_write : 1;
        bool user_super : 1;
        bool write_through : 1;
        bool disable_caching : 1;
        bool accessed : 1;
        bool dirty : 1;
        bool page_attr_table : 1;
        bool global : 1;
        uint8_t available : 3;
        uint64_t addr : 52;
} page_table_entry;

typedef struct
{
        page_table_entry entries[MAX_TABLE_ENTRIES];
} page_table;

/* new page map structures are created if they do not already exist */
static page_table_entry *
get_page_table_entry_by_index(const page_index *ind)
{
        page_dir_entry *ent = &pml4->entries[ind->pdpt];
        page_dir *pdpt;
        if (!ent->present)
        {
                pdpt = free_zero_page();
                *ent = (page_dir_entry)
                {
                        .addr = (uintptr_t)pdpt >> 12,
                        .present = true,
                        .read_write = true,
                };
        }
        else
                pdpt = (page_dir *)(uintptr_t)(ent->addr << 12);
        ent = &pdpt->entries[ind->pdt];
        page_dir *pdt;
        if (!ent->present)
        {
                pdt = free_zero_page();
                *ent = (page_dir_entry)
                {
                        .addr = (uintptr_t)pdt >> 12,
                        .present = true,
                        .read_write = true,
                };
        }
        else
                pdt = (page_dir *)(uintptr_t)(ent->addr << 12);
        ent = &pdt->entries[ind->pt];
        page_table *pt;
        if (!ent->present)
        {
                pt = free_zero_page();
                *ent = (page_dir_entry)
                {
                        .addr = (uintptr_t)pt >> 12,
                        .present = true,
                        .read_write = true,
                };
        }
        else
                pt = (page_table *)(uintptr_t)(ent->addr << 12);
        return &pt->entries[ind->page];
}

void
map_page(const void *virt_addr, const void *phys_addr)
{
        page_index ind = index_virtual_addr(virt_addr);
        page_table_entry *page_ent = get_page_table_entry_by_index(&ind);
        *page_ent = (page_table_entry)
        {
                .addr = (uintptr_t)phys_addr >> 12,
                .present = true,
                .read_write = true,
        };
}

void
identity_map_pages(const void *first_page, const void *last_page)
{
        uintptr_t page = (uintptr_t)first_page;
        for (; page < (uintptr_t)last_page; page += PAGE_SIZE)
                map_page((const void *)page, (const void *)page);
        log_info("identity mapped pages");
}

void
load_page_map(void)
{
        __asm__("mov %0, %%cr3\n"
                :
                : "r" (pml4));
}
