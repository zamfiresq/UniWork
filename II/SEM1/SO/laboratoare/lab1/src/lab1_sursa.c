#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

// ex 2
void ex2() {
      printf("PID = %d, UID = %d, GID = %d\n", getpid(), getuid(), getgid());

	exit(0);
}

// ex 3
void ex3() {
     char buffer[1024];
      ssize_t bytes_read;

      while ((bytes_read = read(0, buffer, sizeof(buffer))) > 0) {
            ssize_t bytes_written = 0;
            while (bytes_written < bytes_read) {
                  ssize_t result = write(1, buffer + bytes_written, bytes_read - bytes_written);
                  if (result < 0) {
                        perror("write");
                        exit(1);
                  }
                  bytes_written += result;
            }
      }
      if (bytes_read < 0) {
            perror("read");
            exit(1);
      } 
}

// programul de la ex 3 citeste date din stdin si le scrie in stdout
// comanda cp face acelasi lucru, dar folosind fisiere
// putem simula cp folosind redirectionarea ./lab1_sursa < lab1_sursa.c > copie.c


// ex 4
int ex4(int argc, char *argv[]) {
      if (argc != 2) {  // verificam daca avem un singur argument in plus
        fprintf(stderr, "Usage: %s <director>\n", argv[0]);
        return 1;
    }

    char *dirname = argv[1];
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
      return 0;
}


// ex 5
void ex5() {
      pid_t pid = getpid(); // proces curent
      uid_t uid = getuid(); // user curent
      gid_t gid = getgid(); // grup curent

      printf("PID: %d, UID: %d, GID: %d\n", pid, uid, gid);
}


// ex 6
void ex6(int argc, char *argv[], char *envp[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <NumeVariabila>\n", argv[0]);
        return;
    }

    char *var_name = argv[1];
    int len = strlen(var_name);

    for (int i = 0; envp[i] != NULL; i++) {
        // fiecare envp[i] are forma NAME = VALUE
        if (strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=') {
            printf("%s\n", envp[i] + len + 1);  // afisam valoarea variabilei
            return;
        }
    }

    printf("Variabila %s nu a fost gasita.\n", var_name);
}



// main
int main(int argc, char *argv[], char* envp[]) {
      // ex2();
      // ex3();
      // ex4(argc, argv);
      // ex5();
      // ex6(argc, argv, envp);

      return 0;
}