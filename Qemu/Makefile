# Налаштування компілятора та інструментів
CC = ia16-elf-gcc
LD = ia16-elf-ld
OBJCOPY = ia16-elf-objcopy

# Прапорці компіляції
CFLAGS = -ffreestanding -Os -nostdlib -fno-PIE
LDFLAGS = -T link.ld --oformat binary

# Файли проекту
OBJS = boot.o main.o
TARGET = boot.bin

# Основна ціль
all: $(TARGET)

# Лінкування бінарного файлу
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

# Компіляція асемблера
boot.o: boot.S
	$(CC) -c boot.S -o boot.o

# Компіляція C коду
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Очистка проекту
clean:
	rm -f $(OBJS) $(TARGET)

# Запуск у QEMU (зручно для тестів)
run: $(TARGET)
	qemu-system-x86_64 \
  -bios ../../../coreboot/build/coreboot.rom \
  -drive file=boot.bin,format=raw,if=none,id=drive0 \
  -device ide-hd,drive=drive0,cyls=1,heads=1,secs=1 \
  -serial stdio

