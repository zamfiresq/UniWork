#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFSIZE	4096

struct msgbuf
{
    long mtype;
    char mtext[BUFSIZE];
};

int main(int argc, char *argv[])
{
    int msgid, n;
    key_t key;
    pid_t pid;
    struct msgbuf sndbuf, rcvbuf;

    if(argc < 2){
        printf("Usage: %s <key file name>\n", argv[0]);
    exit(0);
    }

    if((key = ftok(argv[1], 10300)) < 0){
        perror("FTOK");
    exit(1);
    }

    if((msgid = msgget(key, 0644)) < 0){
        perror("MSGGET");
    exit(1);
    }

    pid = getpid();
    while(fgets(sndbuf.mtext, BUFSIZE, stdin) != NULL)
    {
        sndbuf.mtype = pid;
        msgsnd(msgid, &sndbuf, strlen(sndbuf.mtext), 0);
        n = msgrcv(msgid, &rcvbuf, BUFSIZE, pid, 0);
        if(n > 0)
            write(1, rcvbuf.mtext, n);
    }
    return 0;
}
