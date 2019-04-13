#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, 1, SEM_UNDO};

#define xsi_lock(sem_id)   \
    if (semop(sem_id, &p, 1) < 0) { \
        perror("semop p"); \
        exit(EXIT_FAILURE); \
    }

#define xsi_unlock(sem_id) \
    if (semop(sem_id, &v, 1) < 0) { \
        perror("semop v"); \
        exit(EXIT_FAILURE); \
    }

int init_sem(key_t key, int nsems) {
    int id = semget(key, 1, 0666 | IPC_CREAT);
    if (id < 0) {
        perror("semget");
        return -1;
    }

    union semun u;
    u.val = 1;
    if (semctl(id, 0, SETVAL, u) < 0) {
        perror("semctl");
        return -1;
    }

    return id;

}

int main() {
    key_t key;
    int sem_id;


    if ((key = ftok("xsi_sem.c", 'J')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((sem_id = init_sem(key, 1)) == -1) {
        perror("initsem");
        exit(EXIT_FAILURE);
    }


    if (!fork()) {
        xsi_lock(sem_id)
        printf("[XSI_SEM] Child\n");
        xsi_unlock(sem_id)


    } else {
        xsi_lock(sem_id)
        printf("[XSI_SEM] Parent\n");
        xsi_unlock(sem_id)

        wait(NULL);

        // remove the semaphore
        union semun arg;
        if (semctl(sem_id, 0, IPC_RMID, arg) == -1) {
            perror("semctl");
            exit(1);
        }

    }

    return 0;
}


