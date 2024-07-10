/* This program returns status 10 for child process to parent process on exiting. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main ()
{

  pid_t pid;
  int rv = 10;
  printf("Example code\n");
  pid = fork ();
  
    if(pid == 0)
    {
      printf (" CHILD: This is the child process!\n");
      printf (" CHILD: My PID is %d\n", getpid ());
      printf (" CHILD: My parent's PID is %d, groupid:%d\n", getppid(), getpgrp());
	  sleep(100);
      printf (" CHILD: exiting\n");
      exit (rv);/*Child exited and returning the status code as in variable rv*/    }  
    else
	{
	    printf ("PARENT: This is the parent process!\n");
            printf ("PARENT: My PID is %d,groupid:%d\n", getpid(), getpgrp());
            printf ("PARENT: My child's PID is %d\n", pid);
            printf ("PARENT: I'm now waiting for my child to exit()...\n");
      
            //wait(&rv);  /*Waiting for the child's exit */
            printf ("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv));
            printf ("PARENT: I am exiting\n");
    }
    printf("Exits\n");
    return EXIT_SUCCESS;
}

