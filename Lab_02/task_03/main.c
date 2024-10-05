#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define CHILD_N 2
#define ERROR_CANT_FORK 10
#define ERROR_EXEC 11

void check_stat_val(int stat_val, pid_t childpid);

int main(void)
{
    pid_t childpid[2];
    pid_t curr_childpid;
    int stat_val;
    char *executables[2] = {"./lab_02_01_02/app1.out", "./lab_02_02_02/app2.out"};

    for (int i = 0; i < CHILD_N; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            perror("Can't fork.\n");
            return ERROR_CANT_FORK;
        }
        else if (childpid[i] == 0)
        {
            printf("#%d CHILD: pid=%d, ppid=%d, pgrp=%d.\n", i + 1, getpid(), getppid(), getpgrp());
            if (execl(executables[i], executables[i], NULL) == -1)
            {
                printf("Exec error.\n");
                return ERROR_EXEC;
            }
            return 0;
        }
    }
    for (int i = 0; i < CHILD_N; i++)
    {
        curr_childpid = waitpid(childpid[i], &stat_val, 0);
        check_stat_val(stat_val, curr_childpid);
    }
    return 0;
}

void check_stat_val(int stat_val, pid_t childpid)
{
    if (WIFEXITED(stat_val))
        printf("process %d - success, return code: %d.\n", childpid, WEXITSTATUS(stat_val));
    if (WIFSIGNALED(stat_val))
        printf("process %d - non-intercepted signal: %d.\n", childpid ,WTERMSIG(stat_val));
    else
        printf("process %d - no signal.\n", childpid);

    if (WIFSTOPPED(stat_val))
        printf("process %d - stopped: %d.\n", childpid, WSTOPSIG(stat_val));
    else
        printf("process %d - working.\n", childpid);
}
