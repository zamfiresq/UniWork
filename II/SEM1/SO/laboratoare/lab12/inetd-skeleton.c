#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

int passiveTCP(const char *service, int qlen);

#define QLEN 5

struct service
{
	char *name;
	int sv_sock;
	char *port;
	char *sv_prog;
	char *proto; // udp/tcp, pt cazul general in care superserverul serveste si cereri UDP
};

struct service servers[] =
{
	{"echo", -1, "7000", "./echo-inetd", "tcp"},
	{"daytime", -1, "7001", "./daytime-inetd", "tcp"},
	{"time", -1, "7002", "./time-inetd", "tcp"},
	{NULL,-1,NULL,NULL,}
};


int main(int argc, char *argv[])
{
	struct sockaddr_in fsin; /* the from address of a client */
	int alen; /* from-address length */
	fd_set rfds; /* read file descriptor set */
	int fd, nfds;

	struct service *svp;

	// aflati dimensiunea tabelei de descriptori

	// setati pe zero rfds

	// creati sockets pasivi pt serviciile listate in vectorul "servers"
	// Obs. va trebuie un for loop
	// adaugati socket descriptorii in rfds
	FD_ZERO(&rfds);
	
	while (1) {

		// apelati select
		if(select(...) ...
		
		// intr-un for loop verificati care dintre socket descriptori s-a deblocat
		// si apelati corespunzator accept
		for(...)
			if (FD_ISSET(...)
			{
				int ssock;
				char *service;
				char program[256];

				// accept

				// fork
				// daca e procesul copil
					//	inchideti toti file descriptorii mai putin socket-ul de 
					//	serviciu (cel returnat de accept)
					//	duplicati socket-ul returnat de apelul accept de mai sus
					// 	inchideti socketul 
				
						setuid(getuid());
						setgid(getgid());

					// 	apelati exec pt a executa programul corespunzator:
					//	echo, daytime sau time
					//	nu uitati sa apelati exit dupa exec

				// else 
					//procesul parinte inchide socket-ul de serviciu si se 
					// intoarce in loop
			}

	}
}


