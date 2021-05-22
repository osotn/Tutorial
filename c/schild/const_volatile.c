#include <stdio.h>




int main()
{

const volatile int * volatile const port = (const volatile int*) &g;
volatile int i = 5;
volatile int j = i;


printf("p = %p\n", port);
printf("*p = %d\n", *port);

//*port = 6;

}
