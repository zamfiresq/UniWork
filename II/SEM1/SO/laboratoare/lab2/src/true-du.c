#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char* envp[])
{
        int n, fd, count = 0;
	char c;

	if(argc != 2)
		printf("usage: %s <filename>\n", argv[0]), exit(1);

	if((fd = open(argv[1], O_RDWR)) < 0)
		perror("open"), exit(1);
	
	while((n = read(fd, &c, 1)) > 0)
		if( c != '\0')
			count++;
	
	if(n < 0)
		perror("read"), exit(1);

	printf("file size of %s is = %d\n", argv[1], count);

	close(fd);
	exit(0);
}
