#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int  main( )
{
    sigset_t sigset;
    int errno_save;
    errno_save = errno; /* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0) {
        printf("sigprocmask error\n");
        exit(0);
    }
    if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
    if (sigismember(&sigset, SIGQUIT)) printf("SIGQUT ");
    if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
    if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
    /* remaining signals can go here */
    printf("\n");
    errno = errno_save;
}
