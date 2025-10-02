#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int variabilaGlobala = 6;
char buf[] = "Unbuffered write to stdout\n";

int main(int argc, char *argv[], char* envp[]){
    int variabilaLocala = 10;

    // apel sistem write pentru buf
    write(STDOUT_FILENO, buf, strlen(buf)); // avem wirte, folosim fd
    printf("Inainte de fork\n");
    fflush(stdout); // golirea buffer-ului asociat cu stdout

    pid_t pid = fork(); // pid pentru fork
    if (pid == -1){ // daca am pid negativ (< 0)
        perror("EROARE FORK");
        exit(1);

    }else if(pid == 0) { // suntem in procesul copil, deoarece pid-ul este 0
        variabilaGlobala++;
        variabilaLocala++; // incrementare valori
    }else {
        sleep(2); // daca suntem in procesul parinte, pid > 0
                  // sleep suspenda programul dupa 2 secunde de la executie
    }

    printf("PID:%d, GLOBAL:%d, LOCAL:%d\n", pid, variabilaGlobala, variabilaLocala); // se printeaza procesele
    exit(0);

}


// Diferențele majore între rularea interactivă și
// redirecționarea ieșirii către un fișier constau
// în modul în care sunt afișate și ordinea exactă
// în care mesajele sunt scrise în fișierul rezultat (out).
