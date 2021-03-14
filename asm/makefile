all: test.asm
	nasm -f elf32 test.asm -o test.o -ggdb
	ld -m elf_i386 test.o -o test -g
clean:
	rm -f *.o test
