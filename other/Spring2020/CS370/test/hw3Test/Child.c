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

    void* shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    char message[] = "Hello Parent!";
    sprintf(shm_ptr, "%s", message);
    //printf("shm_ptr = %s\n", shm_ptr);

    shm_unlink(shm_name);
    return 0;
}