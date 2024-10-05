#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int childpid;

    childpid = fork();
    if (childpid == -1)
    {
        perror("Can't fork.\n");
        return 1;
    }
    else if (childpid == 0)
    {
        while(1)
        {
            printf("Child PID: %d\n", getpid());
            usleep(100000);
        }
        return 0;
    }
    else
    {
        while(1)
        {
            printf("Parent PID: %d\n", getpid());
            usleep(100000);
        }
        return 0;
    }
    return 0;
}