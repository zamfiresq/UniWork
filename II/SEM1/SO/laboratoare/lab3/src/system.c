#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[], char* envp[]) {

    // in cazul in care nu avem argumente in linia de comanda
    if (argc < 2) {
        perror("EROARE: NU EXISTA ARGUMENTE\n");
        exit(1);
    }

    // FORK
    pid_t pid = fork();
    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    }

    // procesul copil
    if (pid == 0) {
        char *cmdArg[argc]; // argumente

        for(int i = 1; i <= argc; i++){
            cmdArg[i - 1] = argv[i];
        }
        cmdArg[argc - 1] = NULL;

        execvp(cmdArg[0], cmdArg);

        // eroare
        perror("EROARE EXECVP");
        exit(1);
    }


    // procesul parinte, folosind wait
    int status;
    wait(&status);

    if(WIFEXITED(status)){
        printf("Status=%d\n", WEXITSTATUS(status));
    }

    exit(0);
}