#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int flag = 0;

void sig_handler(int sig_numb)
{
    flag = 1;
    printf("Handler for signal %d is set\n", sig_numb);
}

int main()
{
    int fd[2];
    pid_t childpid_arr[2];

    if (pipe(fd) == -1)
    {
        perror("Can't pipe()\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("Can't signal()\n");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    for (int i = 0; i < 2; ++i)
        if ((childpid_arr[i] = fork()) == -1)
        {
            perror("error: can't fork");
            exit(EXIT_FAILURE);
        }
        else if (childpid_arr[i] == 0)
        {
            char *message;
            if (i == 0)
                message = "aaammmmmmmmmmm\n";
            else
                message = "rrrr\n";

            if (flag)
            {
                printf("%d %s", getpid(), message);
                close(fd[0]);
                write(fd[1], message, strlen(message));
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("%d no signal\n", getpid());
                exit(EXIT_FAILURE);
            }
        }

    for (size_t i = 0; i < 2; i++)
    {
        pid_t w_pid;
        int status;
        w_pid = wait(&status);
        if (WIFEXITED(status))
			printf("%d exited with code %d\n", w_pid, WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("%d recieved signal %d\n", w_pid, WTERMSIG(status));
		else if (WIFSTOPPED(status))
			printf("%d recieved signal %d\n", w_pid, WSTOPSIG(status));  
    }
    char elem;
    close(fd[1]); 
    printf("%d received:\n", getpid());
    for (int i = 0; i < 2; i++)
    {
        do {
            read(fd[0], &elem, 1);
            printf("%s", &elem);
        } while (elem != '\n');
    }
    return 0;
}