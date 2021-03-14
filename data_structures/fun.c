#include <stdio.h>

int fun(int a)
{
  return 4;
}


int main()
{
    int fun();
    int res = fun(4);
    printf("fun() = %d\n", res);
    return 0;
}

