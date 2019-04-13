#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {

    int pfds[2];
    char buf[30];
    pid_t chpid;

    pipe(pfds);

    if (!(chpid = fork())) {
        char *msg = "test";
        write(pfds[1], msg, 5);
        printf("[PIPE] child: wrote %lu bytes, msg:%s\n", strlen(msg), msg);
        printf("[PIPE] Child: Exiting, %d\n", EXIT_SUCCESS);
        exit(EXIT_SUCCESS);
    } else {
        read(pfds[0], buf, 5);
        printf("[PIPE] parent: read %lu bytes, msg:%s\n", strlen(buf), buf);
        waitpid(chpid, NULL, 0);
    }

    return 0;
}