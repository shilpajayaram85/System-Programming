#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define QUEUE_NAME "/myqueue"
#define MAX_SIZE 1024

void send_message(mqd_t mq, const char *message, unsigned int priority) {
    if (mq_send(mq, message, strlen(message) + 1, priority) == -1) {
        perror("mq_send");
        exit(1);
    }
    printf("Sent: %s with priority %u\n", message, priority);
}

void receive_message(mqd_t mq) {
    char buffer[MAX_SIZE];
    unsigned int priority;

    if (mq_receive(mq, buffer, MAX_SIZE, &priority) == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Received: %s with priority %u\n", buffer, priority);
}

int main() {
    mqd_t mq;
    struct mq_attr attr;

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

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process - acts as the receiver
        sleep(2); // Wait to ensure messages are sent first
        while (1) {
            receive_message(mq);
        }
    } else {
        // Parent process - acts as the sender
        send_message(mq, "Low priority message", 1);
        send_message(mq, "Medium priority message", 2);
        send_message(mq, "High priority message", 3);
        
        // Sending exit message to stop the receiver
        send_message(mq, "exit", 4);

        // Wait for child process to finish
        wait(NULL);
    }

    // Close and unlink the message queue
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}

