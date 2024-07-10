#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    char *args[] = { "ls", "-l", NULL };
    printf("Before execv\n");
    execv("/bin/ls", args);
	//execl("/bin/ls", "la", "-l", "NULL");
    fprintf(stderr, "execv failed: %s\n", strerror(errno));
    return 1;
}

