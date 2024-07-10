/* It demonstrates changes to global variable is local to the process */
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>

int x=1;
int main()
{
pid_t pid,a=5;
int ret;
printf("hello\n");
	
pid = fork();
if(pid ==0)
{
	
	printf("\nchild has x = %d,a=%d\n",++x,++a);
//	exit(0);
}
else
{
	wait(NULL);
//	a=a+10;
	printf("\nparent has x = %d,a=%d\n",--x,--a);
}
    printf("Bye from process %d with x = %d\n",getpid(),x);
}
	

