#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
int fd;
char *addr;
struct stat sb;


fd = shm_open(argv[1], O_RDONLY, 0); /* Open existing object */
if (fd == -1)
	perror("shm_open");
/* Use shared memory object size as length argument for mmap()
and as number of bytes to write() */
if (fstat(fd, &sb) == -1)
	perror("fstat");
addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
if (addr == MAP_FAILED)
	perror("mmap");
if (close(fd) == -1); /* 'fd' is no longer needed */
	perror("close");
write(1, addr, sb.st_size);
printf("\n");
exit(EXIT_SUCCESS);
}
