#include <stdio.h>

void fun(int array[])
{
    printf("fun():");
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++)
        printf(" %d", array[i]);
    printf("\n");
}

void fun2(int array[])
{
    printf("fun():");
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++)
        printf(" %d", array[i]);
    printf("\n");
}



main ()
{
    int array[10] = {10, 9, 0};

    fun(array);
    fun2(array);
}
