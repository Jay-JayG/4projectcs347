
#include <stdio.h>// for printf(), perror()
#include <stdlib.h>// for exit()
#include <unistd.h>// for fork(), execlp(), close()
#include <sys/types.h>


int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("Too many arguments");
        return 0;
    }

    int pfd[2];

    if (pipe(pfd) == -1) {
        perror("Pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        dup2(pfd[0], 0);
        close(pfd[1]);
        execlp("/usr/bin/wc", "wc", "-l", (char *)NULL);
        perror("Exec");
    } else {
        dup2(pfd[1], 1);
        close(pfd[0]);
        if (argc == 2) {
            execlp("/bin/ls", "ls", "-1a", argv[1], (char *)NULL);
        } else {
            execlp("/bin/ls", "ls", "-1a", (char *)NULL);
        }
    }

    return 0;
}