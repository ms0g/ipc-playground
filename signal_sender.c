#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <signal.h>


int main(void) {
    union sigval sv;

    // Get the pid of the receiver
    char line[10];
    FILE *command = popen("pidof signal_receiver", "r");

    fgets(line, 10, command);

    pid_t pid = strtoul(line, NULL, 10);
    pclose(command);

    sv.sival_int = 12;

    if (sigqueue(pid, SIGUSR1, sv) < 0)
        perror("sigqueue");

    printf("[SIGNAL] sender: sent %lu bytes, msg:%d\n", sizeof(int), sv.sival_int);

    return 0;
}