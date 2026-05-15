#include "./ulib/types.h"
#include "./ulib/user.h"

#define STDOUT 2

int main()
{
    printf(STDOUT, "Hello world from user space\n");
    return 1234;
}
