#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int fd;
    pid_t chpid;
    struct flock flk = {F_WRLCK, SEEK_SET, 0, 0, 0};
    flk.l_pid = getpid();

    if ((fd = open("flocking.c", O_RDWR)) == -1)
        perror("open");

    if (!(chpid = fork())) {
        printf("[FLOCKING] child: Trying to get lock...\n");

        if (fcntl(fd, F_SETLKW, &flk) == -1) {
            perror("fcntl");
            exit(1);
        }

        printf("[FLOCKING] child: got lock\n");
    } else {
        printf("[FLOCKING] parent: Trying to release lock...\n");

        flk.l_type = F_UNLCK;

        if (fcntl(fd, F_SETLK, &flk) == -1) {
            perror("fcntl");
            exit(1);
        }

        printf("[FLOCKING] parent: Unlocked.\n");
        waitpid(chpid, NULL, 0);
        close(fd);
    }

    return 0;
}

