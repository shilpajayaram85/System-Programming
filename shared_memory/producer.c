#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SHM_SIZE 1024

int main() {
    int shm_fd;
    void *shm_ptr;
    sem_t *sem;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    sem_wait(sem);
    strcpy((char *)shm_ptr, "Hello from Producer!");
    sem_post(sem);

    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);

    return 0;
}

