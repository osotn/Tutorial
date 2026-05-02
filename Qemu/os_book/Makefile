# Налаштування компілятора та інструментів
#CC = ia16-elf-gcc
CC = gcc -m32
#LD = ia16-elf-ld
LD = ld -m elf_i386
#OBJCOPY = ia16-elf-objcopy
AS = nasm

# Прапорці компіляції
CFLAGS = -ffreestanding -nostdlib -fno-PIE -fno-asynchronous-unwind-tables -fno-ident -Os
LDFLAGS = -T link.ld --oformat binary --nmagic -Os
#ASFLAGS = -f bin

# Файли проекту
OBJS = kernel_main.o
TARGET = image.bin
BOOT_SECT = boot_sect.bin
KERNEL = kernel.bin
KERNEL_ENTRY = kernel_entry.o

SECS_NUM = 3


# Основна ціль
all: $(TARGET)

# Target
$(TARGET): $(BOOT_SECT) $(KERNEL)
	cat $(BOOT_SECT) $(KERNEL) > $(TARGET)


# Bootloader
$(BOOT_SECT): boot_sect.asm
	$(AS) -f bin boot_sect.asm -o $(BOOT_SECT)

$(KERNEL_ENTRY): kernel_entry.asm
	$(AS) -f elf kernel_entry.asm -o $(KERNEL_ENTRY)

$(KERNEL): $(KERNEL_ENTRY) $(OBJS)
	$(LD) $(LDFLAGS) $(KERNEL_ENTRY) $(OBJS) -o $(KERNEL)

# Компіляція C коду
kernel_main.o: kernel_main.c
	$(CC) $(CFLAGS) -c kernel_main.c -o kernel_main.o

# Очистка проекту
clean:
	rm -f $(OBJS) $(TARGET) $(BOOT_SECT) $(KERNEL) $(KERNEL_ENTRY) $(BOOT_SECT)

# Запуск у QEMU (зручно для тестів)
run: $(TARGET)
	qemu-system-x86_64 \
  -bios ../../../../coreboot/build/coreboot.rom \
  -drive file=$(TARGET),format=raw,if=none,id=drive0 \
  -device ide-hd,drive=drive0,bus=ide.0,unit=0,cyls=1,heads=1,secs=$(SECS_NUM) \
  -serial stdio

