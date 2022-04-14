#ifndef PAGEALLOC_H_hk3M4CWWXn3e9ry3qVVjw4g46GRBNyV2
#define PAGEALLOC_H_hk3M4CWWXn3e9ry3qVVjw4g46GRBNyV2

#include <stddef.h>

#define PAGE_SIZE 0x1000

void
init_page_alloc(void);

void *
free_page(void);

void
lock_page(const void *page);

void
unlock_page(const void *page);

void *
free_zero_page(void);

void *
free_cont_pages(size_t cnt);

void
lock_pages(const void *page, size_t cnt);

void
unlock_pages(const void *page, size_t cnt);

#endif
