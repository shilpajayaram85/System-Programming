#include <unistd.h>
#include <stdio.h>

int main() {
    char *env[] = { "PATH=/usr/bin:/bin", NULL };
    printf("Before execle\n");
    execle("/bin/ls", "ls", "-l", (char *)0, env);
    printf("After execle\n"); // This line will not be executed if execle is successful
    return 0;
}

