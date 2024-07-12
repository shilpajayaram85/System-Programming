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
    int msg_priority = 0;

    // Set message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    // Create and open the message queue
    mq = mq_open("/myqueue", O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    // Prepare the message
    strcpy(buffer, "Hello, POSIX message queue!");

    // Send the message
    if (mq_send(mq, buffer, strlen(buffer) + 1, msg_priority) == -1) {
        perror("mq_send");
        exit(1);
    }

    // Close the message queue
    mq_close(mq);

    return 0;
}

