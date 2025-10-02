#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    int fd, n;
    char buf[4096];

    if(argc < 2)
        printf("usage: %s <fifo name>\n", argv[0]), exit(0);


    key_t key = ftok(argv[1], 6789);
    if((qid = msgget(key, IPC_CREAT |0644)) < 0)
        perror("open fifo"), exit(1);

    while(fgets(buf, 4096, stdin) != NULL)
    {
        write(fd, buf, strlen(buf));
        n =  read(fd, buf, 4096);
        if(n > 0)
            write(1, buf, n);
    }
    close(fd);
    return 0;
}
