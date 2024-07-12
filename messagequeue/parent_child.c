#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>

#define QUEUE_NAME "/myqueue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

void send_message(mqd_t mq) {
    char buffer[MAX_SIZE];
    unsigned int priority = 0;

    printf("Enter a message to send (type 'exit' to quit): ");
    fgets(buffer, MAX_SIZE, stdin);

    // Remove newline character
    buffer[strcspn(buffer, "\n")] = '\0';

    if (mq_send(mq, buffer, strlen(buffer) + 1, priority) == -1) {
        perror("mq_send");
        exit(1);
    }

    if (strcmp(buffer, MSG_STOP) == 0) {
        printf("Sender exiting.\n");
        exit(0);
    }
}

void receive_message(mqd_t mq) {
    char buffer[MAX_SIZE];
    unsigned int priority;

    if (mq_receive(mq, buffer, MAX_SIZE, &priority) == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Received message: %s\n", buffer);

    if (strcmp(buffer, MSG_STOP) == 0) {
        printf("Receiver exiting.\n");
        exit(0);
    }
}

int main() {
    mqd_t mq;
    struct mq_attr attr;
    pid_t pid;

    // Set message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process - acts as the receiver
        while (1) {
            receive_message(mq);
        }
    } else {
        // Parent process - acts as the sender
        while (1) {
            send_message(mq);
        }
    }

    // Close and unlink the message queue (this code won't be reached)
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}

