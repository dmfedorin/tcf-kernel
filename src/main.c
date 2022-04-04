#include <stdbool.h>
#include "io/text.h"
#include "kernel.h"

void
main(void)
{
        clear_screen();
        init_kernel();
        put_str("hello world\n");
        while (true)
                continue;
}
