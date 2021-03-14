#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (fork() == 0)
        execl("cp", "cp", argv[1], argv[2], NULL);
    wait(NULL);
    printf("copy done\n");
}

