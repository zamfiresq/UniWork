#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 100

int main() {
    int shmid;

    key_t key = IPC_PRIVATE;
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("SHMGET");
        exit(1);
    }

    // Shared memory
    char *shrd_mem = (char *)shmat(shmid, NULL, 0);
    if (shrd_mem == (char *)-1) {
        perror("SHMAT");
        exit(1);
    }

    // Fork
    pid_t pid = fork();

    if (pid < 0) {
        perror("EROARE FORK");
        exit(1);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 10; ++i) {
            sprintf(shrd_mem, "This is child printing %d", i);
            sleep(1);
        }
        exit(0);
    } else {
        // parent process
        for (int i = 0; i < 10; ++i) {
            sleep(1);
            printf("CITESTE PARINTE: %s\n", shrd_mem);
        }
    }

    // detach memory
    if (shmdt(shrd_mem) == -1) {
        perror("SHMDT");
        exit(1);
    }

    // remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("SHMCTL");
        exit(1);
    }
    printf("E SEMN SA TE LASI CA ORICUM NU MERGE\n");

    exit(0);
}
