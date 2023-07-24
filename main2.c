#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

void *routine()
{
    printf("test from threads\n");
    sleep(1);
    printf("test from threads 2\n");
}

int main(int argc, char **av)
{
    int pid = fork();
    if (pid < 0)
        return 1;
    if (!pid)
        printf("im the child process\n");
    else
    {
        wait(&pid);
        printf("im the parent process\n");
    }
        
     return 0;
} 