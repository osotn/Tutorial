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

/*    . = 0x9300;
    .sig : {
        SHORT(0x9300);
    }
*/

    . = 0xAFFE;
    .sig : {
        SHORT(0xAFFE);
    }
}


