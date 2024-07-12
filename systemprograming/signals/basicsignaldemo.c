
#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>

void signal_handler(int signum)
{
	printf("signal_handler for signal : %d invoked\n", signum);
}

void annother_signal_handler(int signum)
{
	printf("another signal_handler for signal : %d invoked\n", signum);
}

int main()
{       int x;
	int sigret = 0;
	signal(SIGINT,signal_handler); // to handle sigint ctrl+c
	signal(SIGQUIT,annother_signal_handler);// to handle sigquit ctrl-backslash
	signal(SIGKILL,signal_handler); // kill -9 pid
	while(1) 
	{	
		sleep(2);
		printf("signal demo: while loop \n");
	}
	printf("can't print this \n");
}

