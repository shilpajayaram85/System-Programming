/*
This program shows how alarm() call is used
It demonstrates that there is only one alarm for a process and if the second alarm call is made in a program before 
the first alarm expires then the second alarm resets the value of the alarm and the first alarm does not expire. 
It can be observed by making the sleep time smaller than the alarm expiry time.
if the sleep time is made bigger than the alarm expiry time then you will observe repeated expiry of alarms.
*/

#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>

void signal_handler(int signum)
{
	printf("signal_handler for alarm : %d invoked\n", signum);
}


int main()
{
	int alarmret = 0;
	typedef void (*sighandler_t)(int);
	sighandler_t sigret = 0;

	sigret = signal(SIGALRM,signal_handler);
	if (SIG_ERR == sigret)
	{
		if (errno != 0) 
		{
			printf("SIGALRM set error %d \n", errno);
		}
		return 1;
	}
	while(1) 
	{
		alarmret = alarm(5);
		printf("alarm demo: while loop %d \n", alarmret);
		sleep(6);
	}
	printf("can't print this \n");
}

