/*
The program demonstrates the usage of signal. The user can set a global flag by sending a signal to the program. After setting the flag the program starts printing some messages which it was not doing earlier. The flag can be reset again by sending a signal again so that the program stops printing the messages again.
*/

#include<stdio.h>
#include<signal.h>
#include<errno.h>

#define NAMESZ 32

int printflag = 0;

void set_flag(int signum)
{
	printf("Enter signal handler function set_flag for : %d\n", signum);
	printflag = 1;
	printf("Exit signal handler function set_flag for : %d\n", signum);
//	exit(0);
}

void reset_flag(int signum)
{
	printf("Enter signal handler function reset_flag for : %d\n", signum);
	printflag = 0;
	printf("Exit signal handler function reset_flag for : %d\n", signum);
}

int main()
{
	int   sigret = 0;
	char  name[NAMESZ];

	signal(SIGINT,set_flag);
    	if (errno != 0) 
	{
		printf("SIGUSR1 set error %d \n", errno);
	}
	signal(SIGUSR2,reset_flag);

	signal(2,set_flag);

    	if (errno != 0) 
	{
		printf("SIGUSR2 set error %d \n", errno);
	}
	while(1) 
	{
		printf("Please enter your name\n");
		scanf("%s", name);
		if (printflag)
		{
			printf("Your name is : %s\n", name);
		}
	}
	printf("can't print this \n");
}

