#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Global variable
int global_var = 10;

int main() {
    pid_t pid;
    int local_var = 20;  // Local variable in main function

    pid = fork();  // Create a new process

    if (pid == 0) {
        // Child process
        printf(" CHILD: This is the child process!\n");

        // Access and modify variables in child
        global_var = 30;
        local_var = 40;

        // Print variable values in child
        printf(" CHILD: Global variable (after modification): %d\n", global_var);
        printf(" CHILD: Local variable (after modification): %d\n", local_var);

    } else if (pid > 0) {
        // Parent process
        printf("PARENT: This is the parent process!\n");

        // Access and modify variables in parent
        global_var = 50;
        local_var = 60;

        // Print variable values in parent
        printf("PARENT: Global variable (after modification): %d\n", global_var);
        printf("PARENT: Local variable (after modification): %d\n", local_var);
    } else {
        // Error handling
        perror("fork failed");
        return EXIT_FAILURE;
    }

    // Print variable values outside forked scope
    printf("Final values - Global variable: %d, Local variable: %d\n", global_var, local_var);

    return EXIT_SUCCESS;
}

