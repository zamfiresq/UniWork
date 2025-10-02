#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // procesul copil

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(44);  // exit code 44
    } else {
        //parinte
        printf("Parent process: PID = %d, waiting for input...\n", getpid());

        int c = getchar();  // se blocheaza pana la apasarea unei taste
        printf("Parent received character: %c\n", c);

        int status;
        waitpid(pid, &status, 0);  // asteapta terminarea copilului

        if (WIFEXITED(status)) {
            printf("Child exited with code: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}