#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>


struct mesg{
    long tip;
    char buf[4096];
}m;


int main(int argc, char *argv[])
{
    int qid, n;
    char buf[4096];

    if(argc < 2)
        printf("Usage: %s <fifo name>\n", argv[0]);
    exit(0);


    key_t key = ftok(argv[1], 6789);
    if((qid = msgget(key, IPC_CREAT |0644)) < 0)
        perror("OPEN FIFO");
    exit(1);


    while((n = msgrcv(qid, m.buf, 4096, 1, 0)) > 0)
        msgsnd(qid, m.buf, n, 0);
    close(qid);


    return 0;
}
