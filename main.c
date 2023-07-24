#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine()
{
    printf("test from threads\n");
    sleep(1);
    printf("test from threads 2\n");
}

int main(int argc, char **av)
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL))
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL))
        return 2;
    if (pthread_join(t1, NULL))
        return 3;
    if (pthread_join(t2, NULL))
        return 4;
    return (0);
} 