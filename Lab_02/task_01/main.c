#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define CHILD_N 2
#define ERROR_CANT_FORK 10

int main(void)
{
    pid_t childpid[2];
    
    for (int i = 0; i < CHILD_N; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            perror("Cant't fork.\n");
            return ERROR_CANT_FORK;
        }
        else if (childpid[i] == 0)
        {
            printf("#%d CHILD: pid=%d, ppid=%d, pgrp=%d.\n", i + 1, getpid(), getppid(), getpgrp());
            sleep(2);
            printf("#%d CHILD: pid=%d, ppid=%d, pgrp=%d.\n", i + 1, getpid(), getppid(), getpgrp());
            return 0;
        }
        else
        {
            printf("PARENT: pid=%d, pgrp=%d, #%dchild_pid=%d.\n", getpid(), getpgrp(), i + 1, childpid[i]);
        }
    }
    return 0;
}
