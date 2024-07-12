#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signum) {
    printf("Caught segmentation fault (SIGSEGV). Exiting gracefully.\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, segfault_handler);

    int *ptr = NULL;  // Null pointer
    *ptr = 42;        // Dereferencing null pointer, causes segmentation fault

    return 0;
}

