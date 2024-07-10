#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    printf("Before execl\n");

    // Using execl to run /bin/ls with the argument -l
    execl("/bin/ls", "ls","-l", (char *)0);

    // If execl fails, the following line will be executed
    fprintf(stderr, "execl failed: %s\n", strerror(errno));
    return 1;
}

