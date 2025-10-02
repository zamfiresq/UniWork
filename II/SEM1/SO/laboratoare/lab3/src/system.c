#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "EROARE: NU EXISTA ARGUMENTE\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    }

    if (pid == 0) {
        char *cmdArg[argc];  // argumente pentru execvp

        for(int i = 1; i < argc; i++){
            cmdArg[i - 1] = argv[i];
        }
        cmdArg[argc - 1] = NULL;

        execvp(cmdArg[0], cmdArg);
        perror("EROARE EXECVP");
        exit(1);
    }

    int status;
    wait(&status);

    if (WIFEXITED(status)) {
        printf("Status=%d\n", WEXITSTATUS(status));
    }

    return 0;
}