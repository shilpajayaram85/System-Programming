#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
int flags, opt, fd;
char * addr;
/* Create shared memory object and set its size */
fd = shm_open("/demo_shm", O_CREAT | O_RDWR, 0666);
if (fd == -1)
	perror("shm_open");
if (ftruncate(fd, 1024) == -1)
	perror("ftruncate");
/* Map shared memory object */
addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (addr == MAP_FAILED)
	perror("mmap");
exit(EXIT_SUCCESS);
}
