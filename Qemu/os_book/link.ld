SECTIONS
{
    . = 0x9000;
    
    .kernel_sector : {
        kernel_entry.o(*)    /* Must be the first */
/*        kernel_main.o(*) */
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(.bss*)
        *(COMMON)
    }

    DISCARD :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.property)
    }

    . = 0x9200;
    .sig : {
        SHORT(0x9200);
    }

    . = 0x93FE;
    .sig : {
        SHORT(0x93FE);
    }
}


