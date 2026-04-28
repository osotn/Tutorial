# .code16 вказує GAS генерувати 16-бітні інструкції
.code16
.global _start
.extern main_c  # ім'я функції з файлу C

_start:
    # Налаштування сегментів (BIOS завантажує нас за адресою 0x7c00)
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    mov $0x7c00, %sp  # Стек росте вниз від початку завантажувача

    call serial_init
    mov $msg_hello, %si
    call serial_print_string

    call main_c       # Виклик вашої функції на C

    mov $msg_hello2, %si
    call serial_print_string

    hlt               # Зупинка, якщо C завершить роботу
loop:
    jmp loop


serial_init:
    push %ax
    push %dx
    mov $0x00, %ah     # Функція 00h: ініціалізація
    mov $0xE3, %al     # 9600, no parity, 1 stop, 8 bit
    xor %dx, %dx       # 0 = COM1
    int $0x14
    pop %dx
    pop %ax
    ret

# Функція друку рядка в Serial
# Вхід: SI = адреса рядка
serial_print_string:
    push %ax
    push %dx
    push %si
    mov $0x00, %dx      # COM1
serial_next_char:
    lodsb               # Завантажує байт з [SI] в AL і інкрементує SI
    cmp $0, %al         # Перевірка на кінець рядка (нуль)
    je serial_done
    mov $0x01, %ah      # Функція BIOS: вивід символу
    int $0x14
    jmp serial_next_char
serial_done:
    pop %si
    pop %dx
    pop %ax
    ret

msg_hello:
    .asciz "Serial: Hello from boot.S !\r\n"

msg_hello2:
    .asciz "Serial: Again from boot.S !\r\n"

# Магічне число завантажувача (останні байти 512-байтового сектора)
#.org 510
#.word 0xAA55

