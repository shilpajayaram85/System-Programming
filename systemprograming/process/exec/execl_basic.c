#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Before execl\n");
    execl("a.out", "a.out", (char *)0);
//	execl("/bin/ls", "ls", "-la", (char *)0);
    printf("After execl\n"); // This line will not be executed if execl is successful
    return 0;
}

