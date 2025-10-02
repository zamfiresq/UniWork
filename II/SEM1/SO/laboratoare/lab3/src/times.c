#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/wait.h>

void runProgram(char *program, char *args[]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    }

    if (pid == 0) {
        // proces copil
        execvp(program, args);
        perror("EROARE EXECLP");
        exit(1);
    } else {
        // proces parinte
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[], char *envp[]) {

    if (argc < 2) {
        printf("EROARE: NU EXISTA ARGUMENTE\n");
        exit(1);
    }

    struct tms start, end;
    clock_t start_real, end_real;

    long clk_tck = sysconf(_SC_CLK_TCK); // ticks pe secunda

    start_real = times(&start);
    runProgram(argv[1], argv + 1);
    end_real = times(&end);

    printf("Timp real: %.2f sec\n", (double)(end_real - start_real)/clk_tck);
    printf("Timp user (parinte): %.2f sec\n", (double)(end.tms_utime - start.tms_utime)/clk_tck);
    printf("Timp system (parinte): %.2f sec\n", (double)(end.tms_stime - start.tms_stime)/clk_tck);
    printf("Timp user (copil): %.2f sec\n", (double)(end.tms_cutime - start.tms_cutime)/clk_tck);
    printf("Timp system (copil): %.2f sec\n", (double)(end.tms_cstime - start.tms_cstime)/clk_tck);

    return 0;
}

// exemplu de rulare: ./times ls