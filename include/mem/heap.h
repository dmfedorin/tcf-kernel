#ifndef HEAP_H_ZZqflhGtw2hxe8p4ztj808QHaOBWUB3R
#define HEAP_H_ZZqflhGtw2hxe8p4ztj808QHaOBWUB3R

#include <stddef.h>

void
init_heap(void);

void *
alloc_mem(size_t size);

void
dealloc_mem(void *ptr);

#endif
