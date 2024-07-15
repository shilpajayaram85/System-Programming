#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"

int main() {
    int fd;
    char buffer[512];

	mkfifo(FIFO_FILE, 0666);
	pid = fork()
	if (pid> 0)
{
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Enter a message: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    return 0;
}

