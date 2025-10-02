#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char* envp[])
{
        int n, fd;
        char c;

	if((fd = open("tempfile", O_RDWR)) < 0)
		perror("open"), exit(1);
	if(unlink("tempfile") < 0)
		perror("unlink"), exit(1);
	printf("temporary file removed\n");
	sleep(10);
	printf("contents of tempfile:\n");
	while(read(fd, &c, 1) > 0)
		write(1, &c, 1);
	close(fd);
	exit(0);
}
