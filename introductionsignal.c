/*
The program shows why signals are needed
It has a global variable which is set to 0 value in the begining of the program.
The program prints certain things only when the flag is 1.
Can you think of a way to set the flag when the program is running?
*/

#include<stdio.h>
#include<signal.h>
#include<errno.h>

#define NAMESZ 32

int printflag = 0;

main()
{
	char  name[NAMESZ];
	

	while(1)
	{
		printf("Please enter your name %d\n", getpid());
		scanf("%s", name);
		if (printflag)
		{
			printf("Your name is : %s\n", name);
		}
	}
	printf("Program never comes here \n");
}













