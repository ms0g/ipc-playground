#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024
#define KEY 0x73616D69

int main() {
    int shmid;
    char *data;


    if ((shmid = shmget(KEY, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
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