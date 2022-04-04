OUTPUT_FORMAT(binary)
ENTRY(main)

SECTIONS {
        . = 0x8e00;

        .text : ALIGN(0x100) {
                *(.text)
        }

        .rodata : ALIGN(0x100) {
                *(.rodata)
        }

        .data : ALIGN(0x100) {
                *(.data)
        }

        .bss : ALIGN(0x100) {
                *(COMMON)
                *(.bss)
        }
}