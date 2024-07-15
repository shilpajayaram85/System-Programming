#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
if(argc !=2)
{
	printf("Usage: %s shardememoryname \n", argv[0]);
	exit(EXIT_FAILURE);
}
if (shm_unlink(argv[1]) == -1)
	perror("shm_unlink");
exit(EXIT_SUCCESS);
}
