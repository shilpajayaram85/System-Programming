#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_sigint(int signum) {
    printf("Received SIGINT (Ctrl+C). Signal handler running...\n");

    // Simulate some work
    sleep(5);

    printf("Exiting SIGINT handler.\n");
}

int main() {
    struct sigaction sa;

    // Set up the structure to specify the new action for SIGINT
    sa.sa_handler = handle_sigint;  // Set the signal handler function
    sa.sa_flags = 0;                // No special flags

    // Initialize the signal mask
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGQUIT);  // Add SIGQUIT to the mask

    // Install the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Running process (PID: %d). Press Ctrl+C to trigger the handler.\n", getpid());

    // Loop indefinitely
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}

