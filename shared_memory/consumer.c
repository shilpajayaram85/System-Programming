#include <stdio.h>
#include <stdlib.h>
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

    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    shm_ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    sem = sem_open(SEM_NAME, 0);

    sem_wait(sem);
    printf("Consumer read: %s\n", (char *)shm_ptr);
    sem_post(sem);

    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);

    return 0;
}


