#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SHM_SIZE 1024

int main() {
    pid_t pid;

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    close(shm_fd);

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    sem_close(sem);

    if ((pid = fork()) == 0) {
        execlp("./producer", "./producer", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == 0) {
        execlp("./consumer", "./consumer", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return 0;
}

