#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[200];
};

int main(void) {
    struct msgbuf buf;
    int msqid;
    key_t key;


    if ((key = ftok("mq_producer.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }


    buf.mtype = 1;
    strncpy(buf.mtext, "test", 5);


    int len = strlen(buf.mtext);

    if (buf.mtext[len - 1] == '\n') buf.mtext[len - 1] = '\0';

    if (msgsnd(msqid, &buf, len + 1, 0) == -1)
        perror("msgsnd");

    printf("[MQ] producer: wrote %d bytes, msg:%s\n", len, buf.mtext);

    return 0;
}