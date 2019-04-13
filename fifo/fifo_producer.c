#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/ex_fifo"

int main(void) {
    char *msg = "test";
    int num, fd;

    if (mkfifo(FIFO_NAME, S_IFIFO | 0666) < 0)
        perror("mknod");

    printf("[FIFO] waiting for consumers...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("[FIFO] got a consumer\n");

    if ((num = write(fd, msg, strlen(msg))) == -1)
        perror("write");
    else
        printf("[FIFO] producer: wrote %d bytes, msg:%s\n", num, msg);
    unlink(FIFO_NAME);
    close(fd);

    return 0;
}