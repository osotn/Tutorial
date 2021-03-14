// OS in 1 hour
// kernel.cpp

#include "types.h"

void printf(char *str)
{
	uint16_t* VideoMemory = (uint16_t*)0xb8000;

	for (int i = 0; str[i] != '\0'; ++i)
		VideoMemory[i] = (VideoMemory[i] & 0x0000) | (str[i] & 0x00FF) | 0x0F00 ;
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor * i=&start_ctors;i!=&end_ctors;i++)
        (*i)();
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magic_number)
{
	printf("!!!!!!!!!!!!!!!!!!!!Hello World!!!!!!!!!!!!!!!!!!!!");
	while(1);
}
