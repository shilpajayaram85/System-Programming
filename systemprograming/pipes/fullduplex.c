#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd1[2];  // Pipe for Process A to Process B
    int pipefd2[2];  // Pipe for Process B to Process A
    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];
    pid_t pid;

    // Create the first pipe (Process A to Process B)
    if (pipe(pipefd1) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe (Process B to Process A)
    if (pipe(pipefd2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    // Create a child process (Process B)
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (Process B)
        close(pipefd1[1]);  // Close write end of pipe1 (Process A to Process B)
        close(pipefd2[0]);  // Close read end of pipe2 (Process B to Process A)

        // Read from pipe1 (Process A to Process B)
        read(pipefd1[0], buffer1, BUFFER_SIZE);
        printf("Process B received: %s", buffer1);

        // Write to pipe2 (Process B to Process A)
        write(pipefd2[1], "Hello from B!", 13);

        close(pipefd1[0]);  // Close read end of pipe1
        close(pipefd2[1]);  // Close write end of pipe2

        _exit(EXIT_SUCCESS);
    } else {
        // Parent process (Process A)
        close(pipefd1[0]);  // Close read end of pipe1 (Process A to Process B)
        close(pipefd2[1]);  // Close write end of pipe2 (Process B to Process A)

        // Write to pipe1 (Process A to Process B)
        write(pipefd1[1], "Hello from A!", 13);

        // Read from pipe2 (Process B to Process A)
        read(pipefd2[0], buffer2, BUFFER_SIZE);
        printf("Process A received: %s", buffer2);

        close(pipefd1[1]);  // Close write end of pipe1
        close(pipefd2[0]);  // Close read end of pipe2

        wait(NULL);  // Wait for child process (Process B) to complete

        exit(EXIT_SUCCESS);
    }

    return 0;
}

