#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int value = 0;
void *runner(void *param);

int main(int argc, char *argv[])
{
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;

    pid = fork();

    if(pid == 0)
    {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        pthread_join(tid, NULL);
        printf("CHILD: value = %d", value);//LINE X
    }
    else if(pid > 0)
    {
        wait(NULL);
        printf("PARENT: value = %d", value);//LINE Y    
    }
}
void *runner(void *param)
{
    value = 3;
    pthread_exit(0);
}