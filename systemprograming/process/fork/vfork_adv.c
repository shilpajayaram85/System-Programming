#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int n = 10;
    pid_t pid = vfork(); // creating the child process

    if (pid == 0) { // if this is the child process
        printf("Child process started\n");
        // Modify n in child process
        n = 20;
        printf("Child process: value of n: %d\n", n);
        _exit(0); // Use _exit() to terminate the child process without flushing stdio buffers
    } else if (pid > 0) { // parent process execution
        printf("Now I am coming back to parent process\n");
        // Modify n in parent process
        n = 30;
        printf("Parent process: value of n: %d\n", n);
    } else {
        // Error handling
        perror("vfork");
        return 1;
    }

    // This line will be executed by both processes (after vfork returns in parent and after _exit in child)
    printf("Final value of n: %d\n", n); // sample printing to check "n" value

    return 0;
}

