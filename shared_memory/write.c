#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
int main(int argc, char *argv[])
{
int fd;
size_t len; /* Size of shared memory object */
char *addr;

fd = shm_open(argv[1], O_RDWR, 0); /* Open existing object */

if (fd == -1)
	perror("shm_open");
len = strlen(argv[2]);
if (ftruncate(fd, len) == -1) /* Resize object to hold string */
	perror("ftruncate");
printf("Resized to %ld bytes\n", (long) len);
addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (addr == MAP_FAILED)
	perror("mmap");
if (close(fd) == -1)
	perror("close"); /* 'fd' is no longer needed */
printf("copying %ld bytes\n", (long) len);
	memcpy(addr, argv[2], len); /* Copy string to shared memory */
exit(EXIT_SUCCESS);
}
