#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello from parent process";
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    // Child process
    if (pid == 0) {
        close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    }
    // Parent process
    else {
        close(fd[0]); // Close read end
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
    }

    return 0;
}
