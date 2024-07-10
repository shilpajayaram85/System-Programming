/***************************************************************************
*	FILENAME : wait.c
*	DESCRIPTION:Contains Code for a program that demonstrates the 
*	use of wait call. It will show the case of Normal and Abnormal
*	Termination of a Child process
*	Invoke the Executable as a.out
*	Copyright 2011 Aricent 
****************************************************************************/
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


/*Comment the next line for showing Normal Termination Case */
 #define ABNORMAL

void print_status(int);
int main()
{
	int exitstatus ,childpid;
	pid_t pid;
	printf("Before fork\n");
	if ((pid = fork())<0)
	{
		printf("Error in Forking \n");
		exit(1);
	}
	else if (pid == 0) /*Child Executing*/
	{
		printf("I am the child \n");
		printf("Child's Pid =%d, My Parent's Pid =%d\n",
			getpid(),getppid());
		
		#ifdef ABNORMAL
			exitstatus/=0;/*Forcing Abnormal Termination*/
		#endif
		
		exit(15);/*Using a Return value that will be fetched*/
	}
	else /*Parent Executing*/
	{
		printf("I am the parent\n");
		printf("MY Child's PID =%d,My Id =%d\n",pid,getpid());
		
		/*Now the parent waits for the Child's Termination*/
			sleep(5);	
		childpid=wait(&exitstatus);
		if (-1 == childpid)
		{
			printf("Error in Executing Wait Function\n");
			exit(1);
		}
		printf("My Child Exited with pid =%d exited\n",childpid);
		print_status(exitstatus);
	}
}

/********************************************************************
*	FUNCTION NAME:print_status
*	DESCRIPTION:Prints the exist exitstatus information of a child
*	NOTES : No Error Checking is done .
*	RETURNS :void 
*********************************************************************/

void print_status(
	int exitstatus)	/*Exit Status Value*/	 
/********************************************************************/
{	

	if (WIFEXITED(exitstatus))
	{
		printf("Normal Termination , exit Status =%d\n",
		WEXITSTATUS(exitstatus));
	}
	else if (WIFSIGNALED(exitstatus))
	{
		printf("Abnormal Termination , Signal No =%d\n",
			WTERMSIG(exitstatus));
	}

	 
}

