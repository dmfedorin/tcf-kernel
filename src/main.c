__asm__("jmp main\n"); /* put first to ensure proper execution */

#include "io/text.h"
#include "kernel.h"
#include "mem/pagealloc.h"

void
main(void)
{
        clear_screen();
        init_kernel();
        hang();
}
