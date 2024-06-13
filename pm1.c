#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);  // Simulating waiting state
        printf("Child Process terminating.\n");
    } else {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);  // Waiting for child process to terminate
        printf("Parent Process terminating.\n");
    }

    return 0;
}

