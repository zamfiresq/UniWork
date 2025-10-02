#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>

volatile sig_atomic_t alarm_fired = 0;

void handler(int sig) {
    alarm_fired = 1;     
    alarm(1);            // alarm este async-signal-safe
}

int main(int argc, char *argv[], char *envp[]) {
    struct passwd *pw;
    if (argc != 2) { fprintf(stderr, "Usage: %s <username>\n", argv[0]); return 1; }

    signal(SIGALRM, handler);
    alarm(1);

    while (1) {
        pw = getpwnam(argv[1]);
        if (pw == NULL) {
            fprintf(stderr, "getpwnam returns NULL\n");
            exit(1);
        }
        printf("UID for %s = %d\n", argv[1], pw->pw_uid);

        if (alarm_fired) {
            alarm_fired = 0;
            struct passwd *pw2 = getpwnam("nobody"); // apel din handler
            if (pw2)
                printf("UID for nobody (from main) = %d\n", pw2->pw_uid);
            else
                printf("nobody not found\n");
        }

        // pentrua nu umple terminalul
        usleep(200000);
    }

    return 0;
}