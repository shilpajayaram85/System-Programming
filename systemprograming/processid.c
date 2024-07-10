#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid;
	printf("Hello\n");
	
	pid = getpid();
	printf("PID : %d\n", pid);
	printf("PPID : %d\n", getppid());

	for(;;);
	return 0;
}
