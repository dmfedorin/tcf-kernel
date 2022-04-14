#include "kernel.h"

#include "mem/layout.h"
#include "util/debug.h"
#include "int/idt.h"
#include "mem/stack.h"
#include <stdbool.h>
#include "mem/heap.h"
#include "mstate/cpu.h"
#include "io/text.h"
#include "mem/pagealloc.h"
#include "mem/paging.h"

static void
init_mem(void)
{
        init_mem_layout();
        init_page_alloc();
        init_paging();
        identity_map_pages((const void *)0x0, (const void *)0x2000000);
        load_page_map();
        init_stack();
        init_heap();
        log_info("initialized memory");
}

static void
init_ints(void)
{
        init_idt_default();
        set_idt_entry(IDT_ENTRY_PAGE_FAULT, INT_DESC_GATE_TYPE_INT,
                      page_fault_isr);
        load_idt();
        __asm__("sti\n");
        log_info("initialized interrupts");
}

void
init_kernel(void)
{
        init_ints();
        init_mem();
        log_info("initialized kernel");
}

void
hang(void)
{
        while (true)
        {
                __asm__("cli\n"
                        "hlt\n");
        }
}

static const char *panic_code_names[] =
{
        "test",
        "general",
};

void
panic(panic_code code)
{
        cpu_state state = get_cpu_state(); /* some of the state will be
                                            * altered due to the panic()
                                            * function call
                                            */
        set_text_attr(TEXT_COLOR_WHITE, TEXT_COLOR_RED);
        clear_screen();
        put_str("an unrecoverable kernel error has occured\n"
                "some information will be displayed to aid debugging\n"
                "\n"
                "panic code: ");
        put_str(panic_code_names[code]);
        put_str("\n\n");
        print_cpu_state(&state);
        hang();
}
