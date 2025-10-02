#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/wait.h>


void runProgram (char *program, char *args[]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    }

    if (pid == 0) {
        // Proces copil
        execvp(program, args);
        perror("EROARE EXECLP");
        exit(1);
    } else {
        // Proces părinte
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[], char* envp[]) {

    // in cazul in care nu avem argumente in linia de comanda
    if (argc < 2) {
        printf("EROARE: NU EXISTA ARGUMENTE\n");
        exit(1);
    }

    struct tms start, end;
    clock_t start_real, end_real;

    start_real = times(&start);
    runProgram(argv[1], argv + 1);
    end_real = times(&end);

    // diferentele de timp
    printf("Real time: %jd\n", (intmax_t)(end_real - start_real));
    printf("User time: %jd\n", (intmax_t)(end.tms_utime - start.tms_utime));
    printf("System time: %jd\n", (intmax_t)(end.tms_stime - start.tms_stime));


    exit(0);
}