// type.h
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

// x86.h
static inline uchar
inb(ushort port)
{
  uchar data;

  asm volatile("in %1,%0" : "=a" (data) : "d" (port));
  return data;
}

static inline void
insl(int port, void *addr, int cnt)
{
  asm volatile("cld; rep insl" :
               "=D" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "memory", "cc");
}

static inline void
outb(ushort port, uchar data)
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void
outw(ushort port, ushort data)
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void
outsl(int port, const void *addr, int cnt)
{
  asm volatile("cld; rep outsl" :
               "=S" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
  asm volatile("cld; rep stosb" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}

static inline void
stosl(void *addr, int data, int cnt)
{
  asm volatile("cld; rep stosl" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}

// ==== uart.c

void microdelay(int ms)
{
//    void ms;
}


#define COM1    0x3f8

static int uart;    // is there a uart?

void
uartputc(int c)
{
  int i;

  if(!uart)
    return;
  for(i = 0; i < 128 && !(inb(COM1+5) & 0x20); i++)
    microdelay(10);
  outb(COM1+0, c);
}

void
uartinit(void)
{
  char *p;

  // Turn off the FIFO
  outb(COM1+2, 0);

  // 9600 baud, 8 data bits, 1 stop bit, parity off.
  outb(COM1+3, 0x80);    // Unlock divisor
  outb(COM1+0, 115200/9600);
  outb(COM1+1, 0);
  outb(COM1+3, 0x03);    // Lock divisor, 8 data bits.
  outb(COM1+4, 0);
  outb(COM1+1, 0x01);    // Enable receive interrupts.

  // If status is 0xFF, no serial port.
  if(inb(COM1+5) == 0xFF)
    return;
  uart = 1;

  // Acknowledge pre-existing interrupt conditions;
  // enable interrupts.
//  inb(COM1+2);
//  inb(COM1+0);
//  ioapicenable(IRQ_COM1, 0);

  // Announce that we're here.
  for(p="xv6...\n"; *p; p++)
    uartputc(*p);
}

//============ console.c

void consputc(char c)
{
    uartputc(c);
}

static void
printint(int xx, int base, int sign)
{
  static char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  uint x;

  if(sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);

  if(sign)
    buf[i++] = '-';

  while(--i >= 0)
    consputc(buf[i]);
}
//PAGEBREAK: 50

// Print to the console. only understands %d, %x, %p, %s.
void
cprintf(char *fmt, ...)
{
  int i, c;//, locking;
  uint *argp;
  char *s;

//  locking = cons.locking;
//  if(locking)
//    acquire(&cons.lock);

  if (fmt == 0) {
//    panic("null fmt");
    return;
  }

  argp = (uint*)(void*)(&fmt + 1);
  for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
    if(c != '%'){
      consputc(c);
      continue;
    }
    c = fmt[++i] & 0xff;
    if(c == 0)
      break;
    switch(c){
    case 'd':
      printint(*argp++, 10, 1);
      break;
    case 'x':
    case 'p':
      printint(*argp++, 16, 0);
      break;
    case 's':
      if((s = (char*)*argp++) == 0)
        s = "(null)";
      for(; *s; s++)
        consputc(*s);
      break;
    case 'c':
      consputc(*argp++);
      break;
    case '%':
      consputc('%');
      break;
    default:
      // Print unknown % sequence to draw attention.
      consputc('%');
      consputc(c);
      break;
    }
  }

//  if(locking)
//    release(&cons.lock);
}

// ======== Interrupts

struct gatedesc {
  uint off_15_0 : 16;   // низькі 16 біт адреси обробника
  uint cs : 16;         // селектор сегмента коду (зазвичай 1 << 3)
  uint args : 5;        // 0 для переривань
  uint rsv1 : 3;        // зарезервовано
  uint type : 4;        // 0xE (32-bit Interrupt Gate)
  uint s : 1;           // 0 для системних сегментів
  uint dpl : 2;         // рівень доступу (0 для ядра, 3 для користувача)
  uint p : 1;           // 1 (присутній)
  uint off_31_16 : 16;  // високі 16 біт адреси
};

struct gatedesc idt[256];

void idtinit_i(void (*f)(), uint i) {
    uint addr = (uint)f;
    cprintf("i = %d, addr = 0x%x\n", i, addr);
    idt[i].off_15_0 = addr & 0xffff;
    idt[i].off_31_16 = addr >> 16;
    idt[i].type = 0xE; // Interrupt Gate
    idt[i].p = 1;
    idt[i].cs = 1 << 3; // Kernel Code Segment
    idt[i].dpl = (i == 64) ? 3 : 0; // Наприклад, 64 - системний виклик (доступний юзеру)
}

void idtinit() {
  extern void vector_default();
  extern void vector0();
  extern void vector32();
  extern void vector33();
  extern void vector36();
  extern void vector64();
  int i;

  for(i=0; i<256; i++)
    idtinit_i(vector_default, i);

  idtinit_i(vector0, 0);
  idtinit_i(vector32, 32);
  idtinit_i(vector33, 33);
  idtinit_i(vector36, 36);
  idtinit_i(vector64, 64);

  // Завантаження IDT в процесор
  static struct {
    ushort limit;
    uint base;
  } __attribute__((packed)) idtr = { sizeof(idt) - 1, (uint)idt };
  
  asm volatile("lidt (%0)" : : "r"(&idtr));
}


#define IOAPIC_ADDR  0xFEC00000
#define REG_TABLE    0x10  // Початок таблиці (2 регістри на кожне IRQ)

// Функція для запису в регістри IOAPIC
void ioapic_write(int reg, uint data) {
    volatile uint *ioapic = (uint*)IOAPIC_ADDR;
    ioapic[0] = reg;      // Вибираємо регістр (IOREGSEL)
    ioapic[4] = data;     // Записуємо дані (IOWIN)
}

void ioapic_enable(int irq, int cpu_apic_id) {
    // Кожне IRQ займає 2 регістри: 0x10 + 2*irq та 0x11 + 2*irq
    // Нижній регістр: номер вектора в IDT + спосіб доставки
    // 33 — це вектор для клавіатури в IDT (IRQ1 + 32)
    ioapic_write(REG_TABLE + 2 * irq, (32 + irq)); 
    
    // Верхній регістр: ID процесора, який отримає переривання
    ioapic_write(REG_TABLE + 2 * irq + 1, cpu_apic_id << 24);
}

#define ID      (0x0020/4)   // ID
#define EOI     (0x00B0/4)   // EOI

#define LAPIC_ADDR  0xFEE00000

static void
lapicw(int index, int value)
{
  volatile uint *lapic = (uint*)LAPIC_ADDR;
  lapic[index] = value;
  lapic[ID];  // wait for write to finish, by reading
}

// Acknowledge interrupt.
void
lapiceoi(void)
{
  lapicw(EOI, 0);
}


#define TIMER      (0x0320/4)
#define TDCR       (0x03e0/4)
#define TICR       (0x0380/4)
#define PERIODIC   0x00020000

void timer_100ms_init() {
  // 1. Дільник частоти на 1 (код 0xB — для багатьох чипсетів QEMU це дільник на 1)
  // В xv6 зазвичай використовують 0x3 (дільник на 16), але для точності в QEMU краще 0xB
  lapicw(TDCR, 0x0000000B); 

  // 2. Встановлюємо вектор 32 та періодичний режим
  lapicw(TIMER, PERIODIC | 32); 

  // 3. Завантажуємо початкове значення для 100мс (100 мільйонів тактів)
  lapicw(TICR, 100000000); 
}

void init_intrs() {
    idtinit();
    ioapic_enable(1, 0);  // Увімкнути клавіатуру (IRQ1) для CPU 0
    ioapic_enable(4, 0);  // Увімкнути UART (IRQ4) для CPU 0
    timer_100ms_init();   // Timer
    asm volatile("sti");  // Дозволити переривання на процесорі
}

struct trapframe {
  // Збережені через pushad
  uint edi, esi, ebp, oesp, ebx, edx, ecx, eax;
  // Збережені вручну
  ushort gs, padding1, fs, padding2, es, padding3, ds, padding4;
  // Штовхнуто вектором
  uint trapno;
  uint err;
  // Штовхнуто самим процесором
  uint eip;
  ushort cs, padding5;
  uint eflags;
};

volatile uint ticks = 0;

// System call numbers
#define SYS_fork    1
#define SYS_exit    2
#define SYS_wait    3
#define SYS_pipe    4
#define SYS_read    5
#define SYS_kill    6
#define SYS_exec    7
#define SYS_fstat   8
#define SYS_chdir   9
#define SYS_dup    10
#define SYS_getpid 11
#define SYS_sbrk   12
#define SYS_sleep  13
#define SYS_uptime 14
#define SYS_open   15
#define SYS_write  16
#define SYS_mknod  17
#define SYS_unlink 18
#define SYS_link   19
#define SYS_mkdir  20
#define SYS_close  21

#define CONS_GET_BUFF_SIZE 512
char consgetbuff[CONS_GET_BUFF_SIZE];
volatile int consgetbuff_counter = 0;

int sys_read(int fd, char *p, int n)
{
    int i;

    //cprintf("Read: %d \n", n);

#if 0
    if (fd != 0) {
        cprintf("fd %d is not impelented\n", fd);
        return -1;
    }
#endif

    if (n > CONS_GET_BUFF_SIZE) {
        cprintf("Error n = %d must be <= %d\n", n, CONS_GET_BUFF_SIZE);
        return -1;
    }

    // Wait data
    asm volatile("sti");
    while(consgetbuff_counter < n);
    asm volatile("cli");

    for (i=0; i < n && i < consgetbuff_counter; i++)
        p[i] = consgetbuff[i];

    if (consgetbuff_counter <= i) {
        consgetbuff_counter = 0;
    } else {
        int j;
        for (j=0; j < consgetbuff_counter - i; j++)
            consgetbuff[j] = consgetbuff[consgetbuff_counter - i - j];
        consgetbuff_counter -= i;
    }
    //consgetbuff_counter -= i;

    //cprintf("Read done\n");
    return i;

}

int sys_write(int fd, char *p, int n)
{
    int i;

#if 0
    if (fd != 1 && fd != 2) {
        cprintf("fd %d is not impelented\n", fd);
        return -1;
    }
#endif

    //cprintf("Write: %d \n", n);

    
    for(i = 0; i < n; i++)
        consputc(p[i]);

    return n;
}

char *sys_sbrk (int size)
{
    static char *buff = (char*)0x40000;
    char *p;

    p = buff;
    buff += size;

    return p;
}

void system_call(struct trapframe *tf)
{
    // 2. Розраховуємо адресу:
    // esp + 0: (зазвичай адреса повернення, якщо був виклик call)
    // esp + 4: перший аргумент (n=0)
    // esp + 8: другий аргумент (n=1)
    uint addr ; /* = esp + 4 + 4*n */
    uint num = tf->eax;

    //cprintf("System call: num in eax = %d \n", num);

    extern void alltraps();
    //cprintf("alltraps() = 0x%p\n", (void*)alltraps);

    //cprintf("tf->esp = 0x%p\n", (void*)tf->oesp);


    //int i;
    //for (i=10; i<13; i++)
    //    cprintf("%d. 0x%p,   0x%x \n", i, tf->oesp, *(uint *)((char*)tf->oesp + (i)*4));

    if (num == SYS_write) {
        int fd    = *(int *)((char*)tf->oesp + (0+10)*4);
        char  *p  = *(char **)((char*)tf->oesp + (1+10)*4);
        int n     = *(int *)((char*)tf->oesp + (2+10)*4);
        tf->eax = sys_write(fd, p, n);
    }
    else if (num == SYS_read) {
        int fd    = *(int *)((char*)tf->oesp + (0+10)*4);
        char  *p  = *(char **)((char*)tf->oesp + (1+10)*4);
        int n     = *(int *)((char*)tf->oesp + (2+10)*4);
        tf->eax = sys_read(fd, p, n);
    }
    else if (num == SYS_sbrk) {
        int size = *(int *)((char*)tf->oesp + (0+10)*4);
        tf->eax = (int)sys_sbrk(size);
    } else {
        cprintf("syscall %d not implemented yet\n", num);
    }
}


void trap(struct trapframe *tf) {
  switch(tf->trapno) {
    case 32: // Таймер
      ticks++;
      //if (ticks % 50 == 0)
      //   cprintf("ticks = %d\n", ticks);
      lapiceoi(); // Підтвердження переривання
      break;
      
    case 33: // Keyboard
      unsigned char c = inb(0x60); // Читаємо скан-код
      cprintf("Key pressed: %x\n", c);
      lapiceoi();
      break;
      
    case 36: // UART (IRQ4)
      char uart_char = inb(0x3F8);
      //cprintf("UART: 0x%x, %c\n", uart_char, uart_char);

      if (consgetbuff_counter < CONS_GET_BUFF_SIZE) {
          consgetbuff[consgetbuff_counter++] = uart_char;
      }

      lapiceoi();
      break;

    case 64: // Software Interrupt (System Call)
      //cprintf("Syscall called!\n");
      system_call(tf);
      break;

    case 255: // Default
      cprintf("Default INR!\n");
      break;

    default:
      cprintf("Unexpected trap %d\n", tf->trapno);
      asm volatile("hlt");
  }
}

int make_syscall(uint num, void* arg1, void* arg2, void* arg3) {
    int retval;
    asm volatile(
        "pushl %4; "          // arg3 (тепер це %4)
        "pushl %3; "          // arg2 (тепер це %3)
        "pushl %2; "          // arg1 (тепер це %2)
        "pushl $0; "          // ФІКТИВНА АДРЕСА ПОВЕРНЕННЯ (для вирівнювання на 10-й індекс)
        "int $64; "           // Виклик переривання (num вже в eax завдяки "a")
        "addl $16, %%esp; "   // Очищення стека, 3 arg + фиктивный
        : "=a" (retval)       // ВИХІД: результат системного виклику з EAX
        : "a" (num),          // ВХІД: номер виклику в EAX
          "r" (arg1), 
          "r" (arg2), 
          "r" (arg3)
        : "cc", "memory"
    );
    return retval;
}

int make_syscall_read(uint fd, char *p, uint n)
{
    return make_syscall(SYS_read, (void *)fd, (void*)p, (void*)n);
}

int make_syscall_write(uint fd, char *p, uint n)
{
    return make_syscall(SYS_write, (void *)fd, (void*)p, (void*)n);
}

//================







#define NUM_ROW     25
#define NUM_COLON   80

void vga_print_string(char *string, int row, int colon, unsigned char color)
{
    char *video_memory = (char*)0xb8000;
    int i = NUM_COLON * row + colon;
    char c;

    while ((c = *string++) != '\0') {
       video_memory[i*2 + 0] = c;
       video_memory[i*2 + 1] = color;
       i++;
    }
}

#define HEX_STRING_PATTER "0x00000000"

void vga_print_hex(unsigned int hex, int n_bits, int row, int colon, unsigned char color)
{
    int i;
    unsigned char c;
    char s[sizeof(HEX_STRING_PATTER)] = HEX_STRING_PATTER;

    for (i = 0; i < n_bits/4; i++) {
        c = (hex >> i*4) & 0xF;
        if (c <= 9)
            c += '0';
        else
            c += 'A' - 10;
        s[2+(n_bits/4-1)-i] = c;
    }

    s[2 + n_bits/4] = '\0';
    vga_print_string(s, row, colon, color);
}


#define SECTSIZE  512


void
waitdisk(void)
{
  // Wait for disk ready.
  while((inb(0x1F7) & 0xC0) != 0x40)
    ;
}

// Read a single sector at offset into dst.
void
readsect(void *dst, uint offset)
{
  // Issue command.
  waitdisk();
  outb(0x1F2, 1);   // count = 1
  outb(0x1F3, offset);
  outb(0x1F4, offset >> 8);
  outb(0x1F5, offset >> 16);
  outb(0x1F6, (offset >> 24) | 0xE0);
  outb(0x1F7, 0x20);  // cmd 0x20 - read sectors

  // Read data.
  waitdisk();
  insl(0x1F0, dst, SECTSIZE/4);
}


void kernel_main() 
{
    vga_print_string("==============Kernel! = v.2", 0, 0, 0x0C /* red */);
#if 0
    vga_print_hex(0x12345678, 32, 1, 0, 0x0C);
    vga_print_hex(0xDEADBEEF, 32, 2, 0, 0x0C);
    vga_print_hex(0x1234,     16, 3, 0, 0x0C);
    vga_print_hex(0xDEAD,     16, 4, 0, 0x0C);
    vga_print_hex(0x12,        8, 5, 0, 0x0C);
    vga_print_hex(0xDE,        8, 6, 0, 0x0C);
#endif

    uartinit();
    cprintf("cprintf hello %d 0x%x %s\n", 10, 0x12345678, "string");


    char *disk_mem = (char*)0x20000;

    int i, n = 8;
    for (i = 0; i < 8; i++)
        readsect(disk_mem + i*512, 17+i);

    vga_print_hex(*(unsigned int*)(&disk_mem[0]),   16, 3, 0, 0x0C);
    vga_print_hex(*(unsigned int*)(&disk_mem[512]), 16, 4, 0, 0x0C);
    
    init_intrs();
    //make_syscall(1, (void*)0xDED1, (void*)0xDED2, (void*)0xDED3);
    //make_syscall(2);
    //make_syscall(24);
    char str[] = "Hello, from syscall write\n";
    make_syscall_write(1, str, sizeof(str));

#if 0
    {
        char buf[10] = {0};
        int i;
        int n = 10;

        make_syscall_read(0, n, buf);
        for (i=0; i<n; i++)
            consputc(buf[i]);
    }
#endif

    {
        int (*p_user_main_func)() = (void*)0x20000;
        cprintf("Try call main from user program....\n");
        int ret = p_user_main_func();
        cprintf("ret = %d from user main()\n", ret);
    }

}

