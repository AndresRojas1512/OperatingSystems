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
    char *message[2] = {"FFFFFFFFFFFFFFFFF", "SSS"};
    int stat_val;
    if (pipe(fd) == -1)
    {
        perror("Pipe error.\n");
        return ERROR_PIPE;
    }
    for (int i = 0; i < CHILD_N; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == - 1)
        {
            perror("Error fork.\n");
            return ERROR_FORK;
        }
        else if (childpid[i] == 0)
        {
            close(fd[0]);
            write(fd[1], message[i], (strlen(message[i]) + 1));
            printf("Message from child process (pid=%d) %s sent to parent.\n", getpid(), message[i]);
            return 0;
        }
        else
        {
            printf("PARENT: pid=%d, pgrp=%d, #%dchild_pid=%d.\n", getpid(), getpgrp(), i + 1, childpid[i]);
        }
    }
    for (int i = 0; i < CHILD_N; i++)
    {
        printf("PARENT: pid=%d, pgrp=%d, #%dchild_pid=%d.\n", getpid(), getpgrp(), i + 1, childpid[i]);
        curr_childpid = waitpid(childpid[i], &stat_val, 0);
        if (curr_childpid == - 1)
        {
            printf("Error waitpid.\n");
        }
        else
        {
            printf("Child process status value: %d, child pid: %d.\n", stat_val, curr_childpid);
            check_stat_val(stat_val, curr_childpid);
            close(fd[1]);
            read(fd[0], message[i], (strlen(message[i] + 1)));
            printf("%s\n", message[i]);
        }
    }
    return 0;
}

void check_stat_val(int stat_val, pid_t childpid)
{
    if (WIFEXITED(stat_val))
        printf("Child process %d finished succesfuly. Return code: %d.\n", childpid, WEXITSTATUS(stat_val));
    else
        printf("Child process finished unsuccesfuly.\n");
    if (WIFSIGNALED(stat_val))
        printf("Child process %d finished with non-intercepted signal: %d.\n", childpid ,WTERMSIG(stat_val));
    else
        printf("Child process %d finished with no signal.\n", childpid);

    if (WIFSTOPPED(stat_val))
        printf("Child process %d stopped: %d.\n", childpid, WSTOPSIG(stat_val));
    else
        printf("Child process %d still working.\n", childpid);
}