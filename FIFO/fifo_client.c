#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "MYFIFO"

int main() {
    int fd;
    char buffer[512];
	
	/*mkfifo
	open
	write
	close
	 
	 open
	 read
	 close */

    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Received message: %s\n", buffer);
    close(fd);

    return 0;
}

