/*__asm__(".code16gcc\n");*/

void print_char(char c) {
    __asm__ __volatile__ (
        "int $0x10"
        :
        : "a" ((0x0e << 8) | (unsigned char)c), "b" (0x0007)
    );
}

/*
void vga_print_char_color(char c, unsigned char color) {
    __asm__ __volatile__ (
        // 1. Малюємо символ з атрибутом кольору (курсор не рухається)
        "mov $0x09, %%ah \n"
        "mov %[col], %%bl \n"
        "mov $0x0001, %%cx \n" // Друкувати 1 раз
        "int $0x10 \n"
        
        // 2. Викликаємо 0x0e для того, щоб BIOS пересунув курсор вперед
        "mov $0x0e, %%ah \n"
        "int $0x10 \n"
        :
        : "a" (c), [col] "rm" (color)
        : "bx", "cx"
    );
}
*/

void vga_print_char_color(char c, unsigned char color) {
    __asm__ __volatile__ (
        // 1. Малюємо символ з атрибутом (кольором)
        // AH = 09h, AL = символ, BH = сторінка, BL = колір, CX = кількість
        "mov $0x09, %%ah    \n"
        "mov %[ch], %%al    \n"
        "mov $0x00, %%bh    \n"
        "mov %[col], %%bl   \n"
        "mov $0x0001, %%cx  \n"
        "int $0x10          \n"
        
        // 2. Тепер рухаємо курсор. 
        // Для цього використовуємо 0x0E, але вона теж малює.
        // Оскільки ми вже намалювали символ з кольором, 
        // 0x0E просто пройдеться зверху, але в деяких BIOS 
        // це може скинути колір. Тому ми робимо це акуратно.
        "mov $0x0e, %%ah    \n"
        "mov %[ch], %%al    \n"
        "int $0x10          \n"
        :
        : [ch] "r" (c), [col] "r" (color)
        : "ax", "bx", "cx"
    );
}


// Вивід символу в Serial
void serial_print_char(char c) {
    __asm__ __volatile__ (
        "mov $0x01, %%ah \n" // Функція 01h: запис символу
        "mov %[ch], %%al \n"
        "mov $0x00, %%dx \n" // 0 = COM1
        "int $0x14       \n"
        :
        : [ch] "rm" (c)
        : "ax", "dx"
    );
}

// Ініціалізація COM1 (9600 бод, 8N1)
void serial_init() {
    __asm__ __volatile__ (
        "mov $0x00, %%ah \n" // Функція 00h: ініціалізація
        "mov $0xE3, %%al \n" // 9600, no parity, 1 stop, 8 bit
        "mov $0x00, %%dx \n" // 0 = COM1
        "int $0x14       \n"
        : : : "ax", "dx"
    );
}

void cls() {
    __asm__ __volatile__ (
        "mov $0x0003, %%ax \n" // ah = 0 (встановити режим), al = 3 (80x25 текст)
        "int $0x10         \n"
        : : : "ax"
    );
}

void main_c() {
    char *str = "Hello from C language compiled as 16 bit code!\r\n";
    cls();
    while (*str) {
        print_char(*str++);
        //vga_print_char_color(*str++, 0x0C);
    }
    serial_init();
    str = "Hello from c (ia16-elf-gcc) output to serial stdout\n";
    while (*str) {
        serial_print_char(*str++);
   }

}

