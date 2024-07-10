/*
This program shows how a signal handler is installed and when it is invoked.
It is invoked when another program sends a signal to this program. 
After the signal has been sent by another program, OS runs the signal handler for the target program when the target program gets the CPU(i.e., is scheduled on the CPU and returning from the kernel mode)
It also shows that signal handlers can't be installed for all types of signals especially SIGKILL.
SIGKILL is a signal which can't be caught and handled, otherwise program may misuse it so that it can't be killed.
*/

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
	signal(SIGINT,signal_handler);
	signal(SIGQUIT,annother_signal_handler);// to handle sigquit ctrl-\
	signal(SIGKILL,signal_handler);
	while(1) 
	{	
		sleep(2);
		printf("signal demo: while loop \n");
	}
	printf("can't print this \n");
	return 0;
}

