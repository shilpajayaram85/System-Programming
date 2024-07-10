#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught signal %d (SIGINT)\n", sig);
}

int main() {
    sigset_t new_set, old_set;

    // Initialize the signal set
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);

    // Block SIGINT and save the current signal mask
    if (sigprocmask(SIG_BLOCK, &new_set, &old_set) < 0) {
        perror("sigprocmask");
        return 1;
    }

    printf("SIGINT blocked. Press Ctrl+C now, it won't terminate the program.\n");
    printf("Performing critical operations...\n");
    sleep(10); // Simulate critical operations

    // Restore the old signal mask (unblocking SIGINT)
    if (sigprocmask(SIG_SETMASK, &old_set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }

    printf("SIGINT unblocked. Press Ctrl+C to terminate the program.\n");

    // Register the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    // Wait for SIGINT signal
    while (1) {
        printf("Waiting for SIGINT...\n");
        sleep(1);
    }

    return 0;
}

