#include <stdio.h>// for printf(), perror()
#include <unistd.h>// for execvp(), close()
#include <fcntl.h>// for open()

int main (int argc, char *argv[]) {

    if (argc < 3) {
        printf("Too few arguments.\n");
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup2(fd, 1);
    close(fd);
    execvp(argv[2], argv + 2);
    perror("execvp");
    return 1;
}