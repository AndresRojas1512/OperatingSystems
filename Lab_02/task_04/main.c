#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define CHILD_N 2
#define ERROR_PIPE 10
#define ERROR_FORK 11
#define ERROR_WAITPID 12

void check_stat_val(int stat_val, pid_t childpid);

int main(void)
{
    pid_t childpid[2];
    pid_t curr_childpid;
    int fd[2];
    char *message[2] = {"aaaaaaaaaaaaammmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm", "rrrr"};
    char buffer[100] = {0};
    int stat_val;
    if (pipe(fd) == -1)
    {
        return ERROR_PIPE;
    }
    for (int i = 0; i < CHILD_N; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            return ERROR_FORK;
        }
        else if (childpid[i] == 0)
        {
            close(fd[0]);
            write(fd[1], message[i], strlen(message[i]) + 1);
            printf("(pid=%d) %s\n", getpid(), message[i]);
            return 0;
        }
        else
        {
            // printf("PARENT: pid=%d, pgrp=%d, #%dchild_pid=%d.\n", getpid(), getpgrp(), i + 1, childpid[i]);
        }
    }

    close(fd[1]);

    for (int i = 0; i < 3; i++)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            printf("%s\n", buffer);
        }
        else
        {
            printf("\n");
        }
    }

    for (int i = 0; i < CHILD_N; i++)
    {
        curr_childpid = waitpid(childpid[i], &stat_val, 0);
        if (curr_childpid == -1)
        {
            return ERROR_WAITPID;
        }
        else
        {
            // printf("Process stat_val: %d, pid: %d.\n", stat_val, curr_childpid);
            // check_stat_val(stat_val, curr_childpid);
        }
    }

    close(fd[0]);
    return 0;
}

void check_stat_val(int stat_val, pid_t childpid)
{
    if (WIFEXITED(stat_val))
        printf("Process %d - success, return code: %d.\n", childpid, WEXITSTATUS(stat_val));
    if (WIFSIGNALED(stat_val))
        printf("Process %d - non-intercepted signal: %d.\n", childpid ,WTERMSIG(stat_val));
    else
        printf("Process %d - no signal.\n", childpid);

    if (WIFSTOPPED(stat_val))
        printf("Process %d - stopped: %d.\n", childpid, WSTOPSIG(stat_val));
    else
        printf("Process %d - working.\n", childpid);
}
