#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("child program running  %d\n", getpid());
	sleep(1);
	execlp("./parent", "parent", NULL);
	return 2;
}
