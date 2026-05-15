[bits 32]
[extern kernel_main]
    call kernel_main
    jmp $


; Макрос для векторів БЕЗ коду помилки (більшість, включаючи IRQ та Syscalls)
%macro VECTOR_NOERR 1
global vector%1
vector%1:
    push 0      ; кладемо фіктивний код помилки
    push %1     ; кладемо номер вектора
    jmp alltraps
%endmacro

; Макрос для векторів, які САМІ кладуть код помилки (напр. Double Fault, Page Fault)
%macro VECTOR_ERR 1
global vector%1
vector%1:
    ; код помилки вже на стеку
    push %1     ; кладемо тільки номер вектора
    jmp alltraps
%endmacro


VECTOR_NOERR 0   ; Division by zero
VECTOR_NOERR 1   ; Debug
VECTOR_ERR   8   ; Double Fault (кладе код помилки сам)
VECTOR_ERR   13  ; General Protection Fault (кладе код помилки сам)
VECTOR_ERR   14  ; Page Fault (кладе код помилки сам)

; Апаратні переривання (IRQ 0-15)
VECTOR_NOERR 32  ; Timer
VECTOR_NOERR 33  ; Keyboard
VECTOR_NOERR 36  ; UART
VECTOR_NOERR 46  ; IDE Disk

global vector_default
vector_default:
    push 0
    push 255 ; умовний номер для невідомих подій
    jmp alltraps


; Системний виклик
VECTOR_NOERR 64  ; System call (0x40)

extern trap      ; Ваша функція void trap(struct trapframe *tf) на C
global alltraps
global trapret

alltraps:
    ; 1. Зберігаємо всі регістри загального призначення
    push ds
    push es
    push fs
    push gs
    pushad       ; Зберігає EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI

    ; 2. Встановлюємо сегменти даних ядра (0x10 — зазвичай Kernel Data)
    mov ax, 0x10 
    mov ds, ax
    mov es, ax

    ; 3. Передаємо вказівник на структуру trapframe (це поточний ESP)
    push esp
    call trap    ; Викликаємо C-функцію: trap(tf)
    
    ; 4. Після повернення з С очищаємо аргумент зі стеку
    add esp, 4

; Точка повернення (можна використовувати для перемикання процесів)
trapret:
    popad        ; Відновлюємо регістри (EDI, ESI, ...)
    pop gs
    pop fs
    pop es
    pop ds
    add esp, 8   ; Очищаємо "код помилки" та "номер вектора"
    iret         ; Повернення з переривання (відновлює EIP, CS, EFLAGS)

