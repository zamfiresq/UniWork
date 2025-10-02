    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // daca avem cel putin un argument 
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return 1;
    }

    // proces copil
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // procesul copil executa programul dat
        // argv[1] = numele programului, argv+1 = lista argumente
        execvp(argv[1], argv + 1);

        // daca execvp esueaza, afisam eroarea
        perror("execvp failed");
        exit(1);
    } else {
        // procesul parinte asteapta terminarea procesului copil
        int status;
        if (wait(&status) == -1) {
            perror("wait failed");
            exit(1);
        }

        // afisare
        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }

    return 0;
}