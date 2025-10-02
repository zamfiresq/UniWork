#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>


// acest program prinde semanlele SIGUSR1 si SIGUSR2 si afiseaza un mesaj corespunzator pentru fiecare

// facem un handler pentru semnalele SIGUSR1 si SIGUSR2
void handler(int sig) {
    if (sig == SIGUSR1) {
        printf("SIGUSR1 PRINS\n");
    } else if (sig == SIGUSR2) {
        printf("SIGUSR2 PRINS\n");
    }

    signal(sig, handler); // reinstalam handlerul
}

int main() {
    // asociem handlerii
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);


    // bucla infinita
    while (true) {
        pause();
    }
}


// compilare si rulare:

// $ gcc -o usr-signal usr-signal.c
// $ ./usr-signal&
// [1] 3873                                 -- PID-ul procesului nostru
// $ jobs                                   -- afisam procesele din background
//[1]  + running    ./usr-signal
// $ kill -USR1 3873
// SIGUSR1 PRINS
// $ kill -USR2 3873
// SIGUSR2 PRINS

// $ kill -TERM 3873                        -- pentru terminarea procesului, prin trimiterea semnalului SIGTERM
//[1]  + terminated  ./usr-signal