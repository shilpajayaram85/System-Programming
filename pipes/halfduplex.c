#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Hello from parent";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Close the unused read end of the pipe
        close(fd[READ_END]);

        // Write to the pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        // Close the write end of the pipe
        close(fd[WRITE_END]);
    } else { // Child process
        // Close the unused write end of the pipe
        close(fd[WRITE_END]);

        // Read from the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child read: %s\n", read_msg);

        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;
}

