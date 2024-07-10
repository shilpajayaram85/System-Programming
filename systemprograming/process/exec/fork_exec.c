/***************************************************************************
*	FILENAME : exec.c
*	DESCRIPTION:Contains Code for a program that demonstrates the 
*	use of exec call
*	Invoke the Executable as a.out
*	Copyright 2010 Aricent 
****************************************************************************/
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int status,retval,childid;
	pid_t pid; /*Return Value of fork*/
	
	printf("Before Fork\n");

	if ((pid = fork())<0)
	{
		printf("Fork  Error:%s",strerror(errno));
		exit(1);
	}
	else if (pid == 0) /*Child*/ 
	{
		retval = execlp("ls","ls","-l",(char*)0);
		if (retval < 0)
		{
			printf("Exec Error:%s",strerror(errno));
//			exit(1);
		}

		printf("Cannot come here");
	}
	else /*Parent Executing*/
	{
		childid = wait(&status);
		printf("Parent = %d,Child  =%d  exited with status =%d" ,
			getpid(),childid,WEXITSTATUS(status));
	}
}


