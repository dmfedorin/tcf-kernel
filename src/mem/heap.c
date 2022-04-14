#include "mem/heap.h"

#include "util/debug.h"
#include "mem/pagealloc.h"

#define HEAP_PAGE_COUNT 2048

static void *heap_ptr;

void
init_heap(void)
{
        heap_ptr = free_cont_pages(HEAP_PAGE_COUNT);
        log_info("initialized heap");
}

typedef struct heap_segment
{
        struct heap_segment *next;
        size_t size;
} heap_segment;

void *
alloc_mem(size_t size)
{
}

void
dealloc_mem(void *ptr)
{
}
