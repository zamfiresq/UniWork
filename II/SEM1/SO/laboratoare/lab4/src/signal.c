#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler(int);

int main(int argc, char *argv[], char *envp[]) {

    pid_t pid;
    void (*old_handler)(int);

    if ((old_handler = signal(SIGCHLD, handler)) == SIG_ERR) {
        perror("SIGCHLD error");
        exit(1);
    }

    if ((pid = fork()) == -1){
        perror("Error fork");
        exit(1);
    }

    if(pid) {
        wait(NULL); // Așteaptă terminarea procesului copilului
        printf("\nPress any key: \n"), getchar(), printf("Done\n\n");
    } else {
        //pid == 0  - procesul copil
        printf("Child pid %d, parent pid %d\n", getpid(), getppid());
        exit(44);
    }
    exit(0);
}

void handler(int signal_number) {
    pid_t pid;
    int status;

    printf("Caught signal %d\n", signal_number); // non-reentrant call
    if((pid = waitpid((pid_t)0, &status, WNOHANG)) == -1) {
        fprintf(stderr, "SIGCHLD, but no one to wait for\n"); // fprintf, not printf
        return;
    }
    printf("Child %d exits with status %d\n", pid, WEXITSTATUS(status)); // non-reentrant call
}
