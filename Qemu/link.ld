SECTIONS
{
    . = 0x7c00;
    
    .boot_sector : {
        boot.o(*)       /* Захопити ВСІ секції з boot.o */
        main.o(*)       /* Захопити ВСІ секції з main.o */
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(.bss*)
        *(COMMON)
    }
   
    . = 0x7dfe;

    .sig : {
        SHORT(0xaa55);
    }

}

