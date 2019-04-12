#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <wait.h>


int main() {
    sem_t semlock;

    if (sem_init(&semlock, 1, 1) < 0) {
        perror("sem_init");
        exit(0);
    }

    if (!fork()) {
        sem_wait(&semlock);
        printf("[POSIX_SEM] child going to post\n");
        sem_post(&semlock);
    } else {
        sem_wait(&semlock);
        printf("[POSIX_SEM] parent wait child\n");
        sem_post(&semlock);

        wait(NULL);
    }

    sem_destroy(&semlock);
}

