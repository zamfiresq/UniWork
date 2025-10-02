#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// functie myprint
void myprint(char *str) {
    char c;

    for(c = *str; c = *str++;)
        write(STDOUT_FILENO, &c, 1);
}


int main(int argc, char* argv[], char* envp[]) {
    pid_t PID = fork();

    // furculita
    if (PID < -1){
        perror("EROARE FORK");
        exit(1);

    }else if(PID == 0){ //proces copil
//        write(STDOUT_FILENO, &c, 1);
        myprint("This is child printing.\n");
        exit(0);
    }else{
//        write(STDOUT_FILENO, &c, 1);
        myprint("This is parent printing.\n");

        exit(0);
    }

}