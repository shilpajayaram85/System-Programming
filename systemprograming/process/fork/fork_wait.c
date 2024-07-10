#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main() {
	int pid      = 0;
	int retval   = 0;
	int status   = 8;
	int lcounter = 0;
	int x = 0;
	pid = fork();
	if (pid == 0)
	{	
	printf("after exec child process id %d \n", getpid());
	printf("Child exiting\n");
	exit(status);
	}
	else 
	{

		printf("Parent\n");
		retval=wait(&status);
		printf("retval %d : status %d\n", retval, status);
		printf("child exit status %d\n",WTERMSIG(status));
		while (lcounter++<1)
		{
			sleep(1);
			printf("parent process id %d \n", getpid());
		}
	}
	return 1;
}

