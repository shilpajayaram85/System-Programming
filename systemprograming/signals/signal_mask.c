
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalhandler(int signo)
{
        printf("\n Received signal:%d", signo);
}

void main()
{
    sigset_t set, oset, pset;

    sigemptyset( &set );
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGABRT);
    
	signal(SIGINT, signalhandler);
    sigprocmask( SIG_BLOCK, &set, &oset );
    printf( "Old set was %8.8ld.\n", oset.__val[0] );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n", pset.__val[0] );

        printf("\n sending SIGINT to self with SIGINT masked");
    kill( getpid(), SIGINT );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n to unmask signal now ..", pset.__val[0] );

    sigprocmask( SIG_UNBLOCK, &set, &oset );


    printf("\n sending SIGINT to self with SIGINT unmasked");
        fflush(stdout);
    printf("\n To end program");
  }


