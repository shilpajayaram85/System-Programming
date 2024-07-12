#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/myqueue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq;
    struct mq_attr attr;

    // Set message queue attributes
    attr.mq_flags = 0;        // Blocking mode
    attr.mq_maxmsg = 10;      // Maximum number of messages
    attr.mq_msgsize = MAX_SIZE;  // Maximum message size
    attr.mq_curmsgs = 0;      // Number of messages currently queued (read-only)

    // Create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Message queue created successfully.\n");

    // Close and unlink the message queue
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}


