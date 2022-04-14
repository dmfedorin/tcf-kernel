#include "mem/stack.h"

#include "mem/pagealloc.h"
#include "util/debug.h"
#include "defs.h"

#define STACK_PAGE_COUNT 1024

static void *stack_ptr;

void
init_stack(void)
{
        stack_ptr = free_cont_pages(STACK_PAGE_COUNT);
        log_info("initialized stack");
}
