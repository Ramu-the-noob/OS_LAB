#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int fd[2];
    //fd[0] = read
    //fd[1] = write
    pid_t pid;
    char message[100] =  "hello from parent";
    char buffer[100];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("received message : %s", buffer );
        close(fd[0]);
    }
    else {
        close(fd[0]);
        write(fd[1], message, sizeof(message));
        close(fd[1]);
    }
    return 0;
}

