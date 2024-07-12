/*
It shows what caution must be taken with signal handlers. 
As explained earlier Signal handlers are just like Interrupt handlers.
For this reason you can't use a primitive like mutex in the signal handler function.
A lock operation on mutex in the signal handler can easily lead to a deadlock if the mutex has been locked in the main program also.
The main problem with locking a mutex in a signal handler is as follows:
Deadlock can occcur as it is difficult to synchronize between the Signal(Interrupt) handler and the main program since it is not possible to predict the time at which the signal(interrupt) will arrive.
The above mentioned point is applicable to any Interrupt handler/Signal handler
*/

#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

int printflag = 1;
pthread_mutex_t gmutex = PTHREAD_MUTEX_INITIALIZER;

void s_handler(int signum)
{
        pthread_mutex_lock(&gmutex);
        printf("Enter signal handler function for : %d\n", signum);
        if (printflag)
                printflag = 0;
        else
                printflag = 1;
        printf("Exit signal handler function for : %d\n", signum);
        pthread_mutex_unlock(&gmutex);
}



int main() {
	int sigret = 0;
	pthread_t thread1;
	signal(SIGINT,s_handler);
    	if (errno != 0) {
			printf("SIGINT set error %d \n", errno);
	}
	while(1) {
		printf("Locking the Mutex\n");
		pthread_mutex_lock(&gmutex);
		//sleep has been used to demonstrate the deadlock with ease
		sleep(100);
		if (printflag)
			printf("printing in while loop if printflag is true\n");
		pthread_mutex_unlock(&gmutex);
	}
	printf("can't print this \n");
}

