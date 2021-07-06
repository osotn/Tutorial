#include <stdio.h>

int main()
{
    FILE *f = fopen("/dev/kmsg", "w");

    if (!f) {
        printf ("Error to open /dev/kmsg \n");
        return 1;
    }

    fprintf(f, "<0> hello kernel");
    fflush(f);
    return 0; 

}
