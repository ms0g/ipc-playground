#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/ex_fifo"

int main(void) {
    char s[300];
    int num, fd;

    printf("[FIFO] waiting for producers...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("[FIFO] got a producer\n");

    if ((num = read(fd, s, 300)) == -1)
        perror("read");
    else {
        s[num] = '\0';
        printf("[FIFO] consumer: read %lu bytes, msg:%s\n", strlen(s), s);
    }

    close(fd);
    return 0;
}