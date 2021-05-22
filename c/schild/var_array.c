#include <stdio.h>


void f(int d)
{
    int array[d];

    printf("d = %d, sizeof(array) = %lu\n", d, sizeof(array)/sizeof(int));
}

int main()
{
    f(10);
    f(20);

}
