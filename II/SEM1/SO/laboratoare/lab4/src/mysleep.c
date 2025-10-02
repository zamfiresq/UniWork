#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

volatile unsigned int seconds_left; // numarul de secunde ramase din timer

void handler(int); // initializare handler

void (*old_handler)(int); // pointer catre handlerul vechi

unsigned int mysleep(unsigned int seconds) { // functionalitate mysleep pentru a prinde semnalul SIGINT in main
    if ((old_handler = signal(SIGALRM, handler)) == SIG_ERR) { // daca nu putem seta handlerul pentru SIGALRM
        perror("EROARE SEMNAL SIGALRM");
        exit(1);
    }
    signal(SIGALRM, handler);
    signal(SIGINT, handler);
    alarm(seconds); // setam un timer pentru SIGALRM
    seconds_left = seconds; // initializam variabila seconds_left cu numarul de secunde
    pause(); // asteptam semnalul SIGALRM
    return alarm(0); // returnam numarul de secunde ramase din timer
}


int main(int argc, char *argv[], char* envp[])
{
    if((old_handler = signal(SIGINT, handler)) == SIG_ERR){ // daca nu putem seta handlerul pentru SIGINT, afisam eroare
        perror("EROARE SEMNAL SIGINT");
    exit(1);
    }

    printf("\nnumber of seconds left = %d\n", mysleep(20)); // apeland mysleep(20) in main, vom astepta 20 de secunde pana la afisarea mesajului

    return 0;
}

void handler(int signum){ // cream acest handler pentru a trata semnalul SIGINT
    return;
}

// compilare si rulare:
// $ gcc -o mysleep mysleep.c
// $ ./mysleep
// ^C
// no of seconds left = ...         -- numarul de secunde ramase din timer


// race condition? apare atunci cand semnalul SIGINT este trimis in timp ce mysleep este in executie
// pentru a combate problema, putem declara variabila seconds ca volatile
