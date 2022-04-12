#include "mem/pagealloc.h"

#include "util/bitmap.h"
#include <stdint.h>
#include "mem/layout.h"
#include <stdbool.h>
#include <stddef.h>
#include "util/debug.h"

#define PAGE_SIZE 0x1000

static const layout_entry *
largest_free_mem_layout_entry(void)
{
        const layout_entry *largest_ent = free_mem_layout_entries()[0];
        for (int i = 0; i < free_mem_layout_entry_count(); ++i)
        {
                if (free_mem_layout_entries()[i]->size > largest_ent->size)
                        largest_ent = free_mem_layout_entries()[i];
        }
        return largest_ent;
}

/* a bit being 0 means an unlocked page, a bit being 1 means a locked page */
static bitmap page_bitmap;

static inline int
bitmap_size_pages(void)
{
        return (uintptr_t)page_bitmap.size_bits / 8 / PAGE_SIZE + 1;
}

static inline void *
bit_to_page(int bit)
{
        return (void *)(uintptr_t)(bit * PAGE_SIZE);
}

static inline int
page_to_bit(const void *page)
{
        return (uintptr_t)page / PAGE_SIZE;
}

static inline void
lock_page_bitmap_pages(void)
{
        int i = page_to_bit(page_bitmap.data);
        for (; i < page_to_bit(page_bitmap.data) + bitmap_size_pages(); ++i)
                lock_page(bit_to_page(i));
}

static inline void
lock_kernel_pages(void)
{
        int last_page = MAX_KERNEL_RESERVED_ADDR / PAGE_SIZE + 1;
        for (int i = 0; i < last_page; ++i)
                lock_page(bit_to_page(i));
}

void
init_page_alloc(void)
{
        page_bitmap = (bitmap)
        {
                .size_bits = total_mem_layout_size() / PAGE_SIZE + 1,
                .data = (uint8_t *)largest_free_mem_layout_entry()->base,
        };
        /* certain pages must not be given when a free one is requested */
        lock_page_bitmap_pages();
        lock_kernel_pages();
        log_info("initialized page allocation");
}

void *
free_page(void)
{
        for (int i = 0; i < page_bitmap.size_bits; ++i)
        {
                if (!bitmap_bit(&page_bitmap, i))
                {
                        lock_page(bit_to_page(i));
                        return bit_to_page(i);
                }
        }
        return NULL;
}

void
lock_page(const void *page)
{
        set_bitmap_bit(&page_bitmap, page_to_bit(page), true);
}

void
unlock_page(const void *page)
{
        set_bitmap_bit(&page_bitmap, page_to_bit(page), false);
}
