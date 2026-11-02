#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

int echod(int fd);
int passiveTCP(const char *service, int qlen);

#define QLEN 5
#define BUFSIZE	4096

/*------------------------------------------------------------------------
* main - Iterative TCP server for DAYTIME service
*------------------------------------------------------------------------
*/
int main(int argc, char *argv[])
{
	struct sockaddr_in fsin; /* the from address of a client */
	char *service = "echo"; /* service name or port number */
	int msock, ssock; /* master & slave sockets */
	int alen; /* from-address length */
	fd_set rfds; /* read file descriptor set */
	fd_set wfds; /* write file descriptor set */
	fd_set afds; /* active file descriptor set */
	int fd, nfds;


	switch (argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			printf("usage: TCPechod [port]\n"), exit(1);
	}

	// create passive socket for echo service
	
	// initialize FD_SETs & add fds of interest

	while (1) {

		if (select(...) < 0)
			printf("select failed: %s\n", strerror(errno)), exit(1);

		
		// check if server socket is ready for reading
		// if so
		//	accept new connection
		//	add new socket descriptor to FD_SET of interest
		

		// loop through all the fds of the process to see if there are any
		// ready for read
		// if any such socket descriptor is found
		//	perform the echo service on that socket
		

		for (fd=0; fd<nfds; ++fd)
			if (fd != msock && FD_ISSET(fd, &wfds))
				if (echod(fd) == 0) 
				{
					(void) close(fd);
					FD_CLR(fd, &afds);
				}
	}
}

int echod(int fd)
{
	char buf[BUFSIZE];
	int cc;

	cc = read(fd, buf, sizeof buf);
	if (cc < 0)
	{
		perror("echod read");
		return -1;
	}
	if (cc && write(fd, buf, cc) < 0)
	{
		perror("echod write");
		return -1;
	}
	return cc;
}


