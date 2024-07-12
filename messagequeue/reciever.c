#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[1024];
    unsigned int msg_priority;

    // Open the message queue
    mq = mq_open("/myqueue", O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    // Receive the message
    if (mq_receive(mq, buffer, 1024, &msg_priority) == -1) {
        perror("mq_receive");
        exit(1);
    }

    // Print the message
    printf("Received message: %s\n", buffer);

    // Close the message queue
    mq_close(mq);

    // Unlink the message queue
    mq_unlink("/myqueue");

    return 0;
}

