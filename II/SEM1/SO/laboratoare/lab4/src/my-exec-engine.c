#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// acest program va executa un program primit ca argument in linia de comanda si va afisa statusul acestuia

int main(int argc, char *argv[], char* envp[]) {

    // in cazul in care nu avem argumente in linia de comanda
    if (argc < 2) {
        fprintf(stderr, "EROARE: NU SUNT SUFICIENTE ARGUMENTE.\n");
        exit(1);
    }

    // FORK - folosim fork pentru a crea un proces copil
    pid_t pid = fork();
    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    }

    // procesul copil - aici vom executa programul primit ca argument in linia de comanda folosind execvp
    if (pid == 0) {
        execvp(argv[1], argv + 1);
        perror("EROARE EXECVP");
        exit(1);
    }

    // procesul parinte folosind wait
    int status;
    wait(&status);

    if(WIFEXITED(status)){ // daca procesul copil a iesit normal
        printf("Status = %d\n", status); // afisam statusul
    }

   exit(0);
}

// compilare si rulare:

// $ gcc -o my-exec-engine my-exec-engine.c
// $ ./my-exec-engine <comanda>
