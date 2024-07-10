#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // size of shared memory segment

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key using ftok
    key = ftok("prooducer.c" ,'A');
	
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Locate the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0644);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read the data from the shared memory segment
    printf("Data read from shared memory: %s\n", data);

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Optional: Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}

