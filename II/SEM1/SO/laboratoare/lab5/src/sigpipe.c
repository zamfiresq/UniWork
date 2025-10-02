#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char* argv[]){


    int fd[2]; // capetele pipe-ului
    pipe(fd);

    if(pipe(fd) < 0){
        perror("EROARE PIPE");
        exit(1);
    }


    int pid = fork();
    if(pid == 0){ // daca sunt in procesul copil

        // nu mai inchidem capatul de scriere al pipe-ului

        char buf[100];
        read(fd[0], buf, 100);
        printf("PROCES COPIL PRIMIT: %s\n", buf);

        close(fd[0]); // inchidem capatul de citire al pipe-ului

    }
    else{
        close(fd[0]); // inchidem capatul de citire al pipe-ului

        char buf[100];
        strcpy(buf, "ACESTA ESTE UN MESAJ DIN PROCESUL PARINTE");
        write(fd[1], buf, strlen(buf) +1 ); // includem si \0

        close(fd[1]); // inchidem capatul de scriere al pipe-ului

        wait(0); // asteptam sa se termine procesul copil
    }

    exit(0);

}


