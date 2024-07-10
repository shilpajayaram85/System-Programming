//Demo code showing double fork to avoid zombie creation

#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    pid_t retpid;
    if ((pid = fork()) < 0)
    {
    printf("fork error");
    }
    else if (pid == 0)
    {
        /* first child */
        if ((pid = fork()) < 0)
            printf("fork error");
        else if (pid > 0)
        {
            printf("\n Parent after fork2 its child is:%d, parent %d to exit now", pid, getpid());
            exit(0);
           
        }
        // since parent had exited this child becomes a zombie and prints below will also not appear as parent has exited
        sleep(2);
        printf("\n second child pid:%d, parent pid = %d  and to exit ", getpid(), getppid()); 
        exit(0);
    }
    printf("\n parent pid:%d, child pid:%d", getpid(), pid);
    if (retpid = waitpid(-1, NULL, 0) ) /* wait for first child */
    {
        printf("\n waitpid return for pid:%d", retpid);

    }
    exit(0);
}

/* output

 Parent after fork2 its child is:1494, parent 1493 to exit now parent pid:1492, child pid:1493                                                      
 waitpid return for pid:1493                                                                                                                        
                                 
                                 
*/


