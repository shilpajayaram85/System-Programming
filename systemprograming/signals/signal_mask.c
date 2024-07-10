
//Demo code to demonstrate masking/unmasking of one or more signals and
// and handling them
//maksed signals are deferred until they are unmasked

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
    printf( "Old set was %8.8ld.\n", oset );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n", pset );

        printf("\n sending SIGINT to self with SIGINT masked");
    kill( getpid(), SIGINT );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n to unmask signal now ..", pset );

    sigprocmask( SIG_UNBLOCK, &set, &oset );


    printf("\n sending SIGINT to self with SIGINT unmasked");
        fflush(stdout);
    printf("\n To end program");
  }


/* output

Old set was 140734745863040.
Pending set is 00000008.

 sending SIGINT to self with SIGINT maskedPending set is 00000008.
 to unmask signal now ..
 Received signal:2
 sending SIGINT to self with SIGINT unmasked
 To end program
*/
