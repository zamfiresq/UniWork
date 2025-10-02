#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[], char* envp[])
{
    DIR *dp;
    struct dirent *dirp;
    char buf[8192];

    if (argc != 2) {
        printf("Usage: %s <dirname>\n", argv[0]);
        exit(0);
    }

    // chdir argv[1]
    if (chdir(argv[1]) < 0) {
        perror("CHDIR");
        exit(1);
    }

    // getcwd in buf
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("CWD = %s\n", buf);
    } else {
        perror("GETCWD");
    }

    exit(0);
}

