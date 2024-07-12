#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process
        printf("Child process running\n");
        exit(EXIT_SUCCESS); // Child exits immediately
    } else {
        // Parent process
        printf("Parent process running and sleeping for 10 seconds\n");
        sleep(10); // Parent sleeps for 10 seconds without calling wait
    }

    return 0;
}

