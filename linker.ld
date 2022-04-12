OUTPUT_FORMAT(binary)
ENTRY(main)

SECTIONS
{
        . = 0x8e00;
        .text : ALIGN(0x10)
        {
                *(.text)
        }
        .rodata : ALIGN(0x10)
        {
                *(.rodata)
        }
        .data : ALIGN(0x10)
        {
                *(.data)
        }
        .bss : ALIGN(0x10)
        {
                *(COMMON)
                *(.bss)
        }
}
