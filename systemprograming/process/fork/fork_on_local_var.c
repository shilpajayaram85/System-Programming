/*this program demonstrates that the changes done to local variables is not shared between parent and child process*/

#include<stdio.h>
#include<unistd.h>

int main ()
{
  int i;
  i = 10;
  if (fork () != 0)
  {
      //while (1)
      //{
          printf ("for Parent ppid =%d and pid =%d\n", getppid (), getpid ());
          i += 20;
          printf ("%d\n", i);
	  sleep(1);
     // }
    }
  else
    {
      //while (1)
      //{
          printf ("for child ppid =%d and pid =%d\n", getppid (), getpid ());
          i += 40;
          printf ("%d\n", i);
	  sleep(1);
     // }
    }
return 0;
}

