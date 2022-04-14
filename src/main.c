__asm__("jmp main\n"); /* put first to ensure proper execution */

#include "io/text.h"
#include "kernel.h"
#include "mem/pagealloc.h"

void
main(void)
{
        clear_screen();
        init_kernel();
        for (int i = 0; i < 1000; ++i)
        {
                void *p = free_page();
                put_ptr(p);
                put_char('\n');
        }
        hang();
}
