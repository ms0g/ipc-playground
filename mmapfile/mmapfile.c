#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <wait.h>
#include <errno.h>

int main() {

    int fd;
    char *data;
    int size;
    sem_t semlock;

    if (sem_init(&semlock, 1, 1) < 0) {
        perror("sem_init");
        exit(0);
    }


    if ((fd = open("test.txt", O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }


    size = getpagesize();
    ftruncate(fd, size);

    data = mmap((caddr_t) 0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == (caddr_t) (-1)) {
        perror("mmap");
        exit(1);
    }

    if (!fork()) {
        char *msg = "test";
        sem_wait(&semlock);
        strncpy(data, msg, 5);
        printf("[MMAP] child: write %lu bytes, msg:%s\n", strlen(msg), msg);
        sem_post(&semlock);
    } else {

        for (int i = 0; i < 10; i++) {
            sleep(1);
            sem_wait(&semlock);
            printf("[MMAP] parent: read %lu bytes, msg:%s\n", strlen(data), data);
            sem_post(&semlock);
        }

        wait(NULL);
        munmap(data, size);
        close(fd);
    }
    return 0;
}

