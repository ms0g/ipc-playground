#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[200];
};

#define KEY 0x73616D69

int main(void) {
    struct msgbuf buf;
    int msqid;


    if ((msqid = msgget(KEY, 0644)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }


    if (msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("[MQ] consumer: read %lu bytes, msg:%s\n", strlen(buf.mtext), buf.mtext);


    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}