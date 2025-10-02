#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <signal.h>

void handler(int nrSemnal) {
    return;
}

void (*oldHandler)(int); // pointer catre handlerul vechi

int main(int argc, char *argv[], char* envp[]) {
    struct passwd *pw; // structura pentru a retine informatiile despre utilizator

    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        exit(0);
    }

    if ((oldHandler = signal(SIGALRM, handler)) == SIG_ERR){
        perror("SIGALRM error");
        exit(1);
    }

    alarm(1);

    int gasit = 0; // variabila pentru a verifica dacă utilizatorul a fost gasit

    while(!gasit) {
        if((pw = getpwnam(argv[1])) == NULL) { // daca pw este NULL, atunci utilizatorul nu a fost gasit
            printf("getpwnam returns NULL\n");
            exit(1);
        }
        printf("Username = %s\n", pw->pw_name);
        gasit = 1; // seteaza variabila gasit pentru a ieși din bucla
    }
    exit(0);
}

// compilare si rulare:
// $ gcc -o pwnam pwnam.c
// $ ./pwnam "username"

// ce ar trebui sa se intample:
// Username = "username"