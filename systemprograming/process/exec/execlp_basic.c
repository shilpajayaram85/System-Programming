#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Before execlp\n");
    execlp("ls", "ls", "-l", (char *)0);
    printf("After execlp\n"); // This line will not be executed if execlp is successful
    return 0;
}

