#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    // Define the environment variable array
    char *env[] = { "PATH=/usr/bin:/bin", NULL };

    printf("Before execle\n");

    // Using execle to run /bin/ls with the argument -l and specified environment
    execle("/bin/ls", "ls", "-l", (char *)0, env);

    // If execle fails, the following line will be executed
    fprintf(stderr, "execle failed: %s\n", strerror(errno));
    return 1;
}

