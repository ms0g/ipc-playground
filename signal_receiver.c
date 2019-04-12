#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


int stop = 0;

static void handler(int sig, siginfo_t *si, void *ucontext);

int main(void) {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);

    while (!stop) { sleep(1); }
    return 0;
}

static void handler(int sig, siginfo_t *si, void *ucontext) {
    stop = 1;
    printf("[SIGNAL] receiver: got %lu bytes, msg:%d\n", sizeof(int), si->si_value.sival_int);
}



