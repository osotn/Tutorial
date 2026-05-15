# Налаштування компілятора та інструментів
#CC = ia16-elf-gcc
CC = gcc -m32
#LD = ia16-elf-ld
LD = ld -m elf_i386
#OBJCOPY = ia16-elf-objcopy
AS = nasm

# Прапорці компіляції
CFLAGS = -ffreestanding -nostdlib -fno-PIE -fno-asynchronous-unwind-tables -fno-ident -Os
LDFLAGS = --oformat binary -N -Os
#LDFLAGS_ELF = -N -Os
#ASFLAGS = -f bin

# Файли проекту
OBJS = kernel_main.o
TARGET = image.bin
BOOT_SECT = boot_sect.bin
KERNEL = kernel.bin
KERNEL_ENTRY = kernel_entry.o

ULIB_DIR = ./ulib
ULIB_OBJ =  $(ULIB_DIR)/ulib.o $(ULIB_DIR)/umalloc.o $(ULIB_DIR)/usys.o $(ULIB_DIR)/printf.o 

UPROGS= sh
#UPROGS= hello

#SECS_NUM = 16
SECS_NUM = 20

# Основна ціль
all: $(TARGET) 

# Target
$(TARGET): $(BOOT_SECT) $(KERNEL) $(UPROGS)
	cat $(BOOT_SECT) $(KERNEL) $(UPROGS) > $(TARGET)

# Bootloader
$(BOOT_SECT): boot_sect.asm
	$(AS) -f bin boot_sect.asm -o $(BOOT_SECT)

$(KERNEL_ENTRY): kernel_entry.asm
	$(AS) -f elf kernel_entry.asm -o $(KERNEL_ENTRY)

$(KERNEL): $(KERNEL_ENTRY) $(OBJS)
	$(LD) $(LDFLAGS) -T link.ld $(KERNEL_ENTRY) $(OBJS) -o $(KERNEL)

# Компіляція C коду
kernel_main.o: kernel_main.c
	$(CC) $(CFLAGS) -c kernel_main.c -o kernel_main.o

$(ULIB)/%.o: $(ULIB)/%.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c -o hello.o

hello: $(ULIB_OBJ) hello.o
	$(LD) $(LDFLAGS) -e main -Ttext 0x20000 -o $@ $^


sh.o: sh.c
	$(CC) $(CFLAGS) -c sh.c -o sh.o

sh: $(ULIB_OBJ) sh.o
	$(LD) $(LDFLAGS) -e main -Ttext 0x20000 -o $@ $^


# Очистка проекту
clean:
	rm -f $(UPROGS) $(OBJS) $(TARGET) $(BOOT_SECT) $(KERNEL) $(KERNEL_ENTRY) $(BOOT_SECT)

# Запуск у QEMU (зручно для тестів)
run: $(TARGET) 
	qemu-system-x86_64 \
  -bios ../../../../coreboot/build/coreboot.rom \
  -drive file=$(TARGET),format=raw,if=none,id=drive0 \
  -device ide-hd,drive=drive0,bus=ide.0,unit=0,cyls=1,heads=1,secs=$(SECS_NUM) \
  -serial stdio

