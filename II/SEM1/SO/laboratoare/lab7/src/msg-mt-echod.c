#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>


#define BUFSIZE	4096

struct mesg
{
    long mtype;
    char mtext[BUFSIZE];
};

int msgid;

void handler(int signo)
{
    if(msgctl(msgid, IPC_RMID, 0) < 0)
        perror("MSGCTL"), exit(1);
}

void *producer(void *p){
    struct mesg *sndbuf = (struct mesg *)p;
    msgsnd(msgid, sndbuf, strlen(sndbuf->mtext), 0);
    return NULL;
}


int main(int argc, char *argv[])
{
    int n;
    key_t key;
    struct mesg msg;
    pthread_t producer_thread;


    if(argc < 2){
        printf("Usage: %s <key file name>\n", argv[0]);
        exit(0);
    }

    if(signal(SIGTERM, handler) < 0){
        perror("SIGNAL");
        exit(1);
    }


    if((key = ftok(argv[1], 10300)) < 0){
        perror("FTOK");
        exit(1);
    }


    if((msgid = msgget(key, IPC_CREAT | 0644)) < 0){
        perror("MSGGET");
        exit(1);
    }


    while((n = msgrcv(msgid, &msg, BUFSIZE, 0, 0)) > 0)
    {
        if(pthread_create(&producer_thread, NULL, producer, &msg))
            exit(1);
        bzero(&msg, sizeof(msg));
    }


    exit(0);
}
