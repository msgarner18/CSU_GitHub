#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char shm_name[] = "Shared_memory";

    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);

    int SIZE = 32;
    ftruncate(shm_fd, SIZE);

    void* shm_ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    pid_t pid = fork();

    if(pid == 0)
    {
        execlp("./Child", "./Child", NULL);
    }
    else{
        wait(NULL);
        printf("shm_ptr = %s\n", shm_ptr);
    }
    return 0;
}