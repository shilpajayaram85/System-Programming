#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define READ_END  0
#define WRITE_END 1

void report_and_exit(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void sigchld_handler(int sig) {
    printf("Parent process received SIGCHLD signal\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipeFDs[2];
    char buf[1024];

    if (pipe(pipeFDs) < 0) report_and_exit("pipe");
    pid_t cpid = fork();
    if (cpid < 0) report_and_exit("fork");

    if (0 == cpid) { // Child process
        close(pipeFDs[WRITE_END]);
        FILE *dest = fopen(argv[2], "w");
        if (!dest) report_and_exit("fopen");

        ssize_t bytesRead;
        while ((bytesRead = read(pipeFDs[READ_END], buf, sizeof(buf) - 1)) > 0) {
            buf[bytesRead] = '\0';  // Null-terminate the string
            //reverse_string(buf);
            fwrite(buf, sizeof(char), bytesRead, dest);
        }
        fclose(dest);
        close(pipeFDs[READ_END]);

        // Send SIGCHLD signal to parent process
        kill(getppid(), SIGCHLD);
        _exit(0);
    } else { // Parent process
        close(pipeFDs[READ_END]);

        signal(SIGCHLD, sigchld_handler);

        FILE *src = fopen(argv[1], "r");
        if (!src) report_and_exit("fopen");

        while (fgets(buf, sizeof(buf), src)) {
            write(pipeFDs[WRITE_END], buf, strlen(buf));
        }
        fclose(src);
        close(pipeFDs[WRITE_END]);

        wait(NULL);  // Wait for child to exit
        printf("Parent process exiting\n");
        exit(0);
    }

    return 0;
}

