#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *data;

    // create the key
    if ((key = ftok("shm_producer.c", 'S')) == -1) {
        perror("ftok");
        exit(1);
    }


    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // attach to the segment to get a pointer to it:
    data = shmat(shmid, (void *) 0, 0);
    if (data == (void *) (-1)) {
        perror("shmat");
        exit(1);
    }

    strncpy(data, "test", SHM_SIZE);
    printf("[SHM] producer: wrote %lu bytes, msg:%s\n", strlen(data), data);


}