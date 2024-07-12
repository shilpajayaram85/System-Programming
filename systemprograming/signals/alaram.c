#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum) {
    printf("Alarm signal received: %d\n", signum);
	exit(1);
}

int main() {
    // Register the alarm signal handler
    signal(SIGALRM, alarm_handler);

    // Set the alarm to go off after 5 seconds
    alarm(5);

    printf("Alarm set for 5 seconds.\n");

    // Pause the program to wait for the alarm signal
    // This can be replaced with your program's logic
    while (1) {
        printf("Waiting for the alarm...\n");
        sleep(1);
    }

    return 0;
}

