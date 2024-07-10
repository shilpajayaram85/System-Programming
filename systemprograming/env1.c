#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *arge[])
{

	int i;
	for(i=0;arge[i];i++)
	{
		printf("%s\n",arge[i]);
	}

	return 0;
}
