
/* Linker script for EorzeOS kernel */

ENTRY(main)

SECTIONS
{
    /* Kernel is loaded at 0x1000 (4KB) */
    . = 0x1000;
    
    /* Code section */
    .text : ALIGN(4096)
    {
        *(.text)
    }
    
    /* Read-only data section */
    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }
    
    /* Data section */
    .data : ALIGN(4096)
    {
        *(.data)
    }
    
    /* BSS section (uninitialized data) */
    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }
}