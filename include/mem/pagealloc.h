#ifndef PAGEALLOC_H_hk3M4CWWXn3e9ry3qVVjw4g46GRBNyV2
#define PAGEALLOC_H_hk3M4CWWXn3e9ry3qVVjw4g46GRBNyV2

void
init_page_alloc(void);

void *
free_page(void);

void
lock_page(const void *page);

void
unlock_page(const void *page);

#endif