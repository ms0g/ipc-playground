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

#define KEY 0x73616D69

int main(void) {
    struct msgbuf buf;
    int msqid;

    if ((msqid = msgget(KEY, 0644 | IPC_CREAT)) == -1) {
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