#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    printf("Before execlp\n");

    // Using execlp to run ls with the argument -l
    execlp("ls", "ls", "-l", (char *)0);

    // If execlp fails, the following line will be executed
    fprintf(stderr, "execlp failed: %s\n", strerror(errno));
    return 1;
}

