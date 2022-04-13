#include "mem/paging.h"

#include "util/debug.h"
#include <stdint.h>
#include <stdbool.h>
#include "mem/pagealloc.h"
#include "libc/string.h"
#include "mem/layout.h"

#define PAGING_TABLE_ENTRIES 512

typedef struct
{
        int pdpt;
        int pdt;
        int pt;
        int page;
} page_index;

static page_index
index_virtual_addr(const void *ptr)
{
        return (page_index)
        {
                .page = (uintptr_t)ptr >> 12 & 0x1ff,
                .pt = (uintptr_t)ptr >> 21 & 0x1ff,
                .pdt = (uintptr_t)ptr >> 30 & 0x1ff,
                .pdpt = (uintptr_t)ptr >> 39 & 0x1ff,
        };
}

/* not to be confused with page table entry */
typedef struct
{
        bool present : 1;
        bool read_write : 1;
        bool user_super : 1;
        bool write_through : 1;
        bool disable_cache : 1;
        bool accessed : 1;
        bool _reserved_0 : 1;
        bool large_pages : 1;
        bool _reserved_1 : 1;
        uint8_t available : 3;
        uint64_t addr : 52;
} paging_table_entry;

/* not to be confused with page table */
typedef struct
{
        paging_table_entry entries[PAGING_TABLE_ENTRIES];
} paging_table;

static paging_table *pml4;

void
init_paging(void)
{
        pml4 = free_page();
        memset(pml4, '\0', PAGE_SIZE);
        log_info("initialized paging");
}

static void
setup_new_paging_table(paging_table *table)
{
        paging_table *new_table = free_page();
        memset(new_table, '\0', PAGE_SIZE);
        *(paging_table_entry *)table = (paging_table_entry)
        {
                .addr = (uintptr_t)new_table >> 12,
                .present = true,
                .read_write = true,
        };
}

static inline bool
paging_table_exists(const paging_table *table)
{
        return ((const paging_table_entry *)table)->present;
}

void
map_page(const void *virt_ptr, const void *phys_ptr)
{
        page_index page_ind = index_virtual_addr(virt_ptr);
        paging_table *pdpt = (paging_table *)&pml4->entries[page_ind.pdpt];
        if (!paging_table_exists(pdpt))
                setup_new_paging_table(pdpt);
        paging_table *pdt = (paging_table *)&pdpt->entries[page_ind.pdt];
        if (!paging_table_exists(pdt))
                setup_new_paging_table(pdt);
        paging_table *pt = (paging_table *)&pdt->entries[page_ind.pt];
        if (!paging_table_exists(pt))
                setup_new_paging_table(pt);
        pt->entries[page_ind.page] = (paging_table_entry)
        {
                .addr = (uintptr_t)phys_ptr >> 12,
                .present = true,
                .read_write = true,
        };
}

void
identity_map_pages(void)
{
        uintptr_t page = 0x0;
        for (; page < 0x4000000; page += PAGE_SIZE)
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
