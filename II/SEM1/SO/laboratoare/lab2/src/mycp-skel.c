#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // pentru strncmp
#include <fcntl.h>

#define BUFSIZE 8192

int main(int argc, char *argv[], char *envp[]) // comenzi terminal
{
    int n;
    char buf[BUFSIZE];


//    if (argc != 3) {
//        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
//        exit(1);
//    }

//    int source_fd = open(argv[1], O_RDONLY); // deschide fișierul sursa pentru citire
//    if (source_fd == -1) {
//        perror("Error opening source file");
//        exit(1);
//    }
//
//    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644); // deschide fișierul destinatie pentru scriere
//    if (dest_fd == -1) {
//        perror("Error opening destination file");
//        exit(1);
//    }

    while ((n = read(0, buf, BUFSIZE)) > 0) // citire de la tastatura
    {
        if (write(1, buf, n) != n)
        {
            perror("WRITE");
            exit(1);
        }

        if(strncmp(buf, "exit", 4) == 0){ // cuvant cheie pentru a iesi din loop ul infinit
            break;
        }

    }

    if (n == -1)
    {
        perror("READ");
        exit(1);
    }

//    close(source_fd);
//    close(dest_fd);

//    printf("File copied successfully: %s -> %s\n", argv[1], argv[2]);
    exit(0);
}

