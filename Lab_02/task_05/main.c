#define _XOPEN_SOURCE 700   
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CHILD_N 2
#define ERROR_PIPE 10
#define ERROR_FORK 11
#define ERROR_WAITPID 12
#define ERROR_SIGNAL 13
#define ERROR_WAIT 14

#define BUFFER_SIZE 100

int flag = 0;

void check_stat_val(int stat_val, pid_t pid);

void catch_sig(int signal);

int main(void)
{
    pid_t childpid[2];
    // char buffer[BUFFER_SIZE];
    // pid_t curr_childpid;
    int fd[2];
    char *message[2] = {"aaaaaaaaaaaaammmmmmmmmmm", "rrrr"};
    int stat_val;

    if (pipe(fd) == -1)
    {
        perror("error: can't pipe\n");
        return ERROR_PIPE;
    }
    if (signal(SIGINT, catch_sig) == -1)
    {
        perror("error: can't signal\n");
        return ERROR_SIGNAL;
    }

    sleep(2);

    for (int i = 0; i < CHILD_N; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            perror("error: can't fork\n");
            return ERROR_FORK;
        }
        else if (childpid[i] == 0)
        {
            if (flag)
            {
                close(fd[0]);
                write(fd[1], message[i], strlen(message[i]) + 1);
                printf("%d %s\n", getpid(), message[i]);
                return 0;
            }
            else
            {
                printf("%d no signal\n", getpid());
                return 0;
            }
        }
    }
    close(fd[1]);
    for (int i = 0; i < CHILD_N; i++)
    {
        if ((childpid[i] = wait(&stat_val)) == -1)
        {
            perror("error: can't wait\n");
            return ERROR_WAIT;
        }
        if (flag)
        {
            read(fd[0], message[i], sizeof(message[i]));
            printf("parent=%d message: %s\n", getpid(), message[i]);
        }
    }
    close(fd[0]);
    return 0;
}

void check_stat_val(int stat_val, pid_t pid)
{
    if (WIFEXITED(stat_val))
        printf("process=%d exited, status=%d\n", pid, WEXITSTATUS(stat_val));
    else if (WIFSIGNALED(stat_val))
        printf("process=%d killed by signal: %d\n", pid ,WTERMSIG(stat_val));
    else if (WIFSTOPPED(stat_val))
        printf("process=%d, stopped by signal: %d\n", pid, WSTOPSIG(stat_val));
    #ifdef WIFCONTINUED
    else if (WIFCONTINUED(stat_val))
        printf("process %d continued\n", pid);
    #endif
}

void handler(int signal)
{
    flag = 1;
}
