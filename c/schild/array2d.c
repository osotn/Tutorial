#include <stdio.h>

int main()
{
    int array[10][20];

    for(int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
            array[i][j] = i * 20 + j;

    int *p = (int *)array;
    for(int i = 0; i < 200; i++)
        printf("%3d. %3d\n", i, p[i]);

    printf("sizeof(array)/sizeof(int) = %d\n", (int)sizeof(array)/sizeof(int));
}
