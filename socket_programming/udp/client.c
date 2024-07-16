#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 16661
#define SERVER_IP "127.0.0.1"
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send message to server
    sendto(sockfd, argv[1], strlen(argv[1]), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    // Receive response from server
    int len = recvfrom(sockfd, (char *)buffer, BUF_SIZE, 0, NULL, NULL);
    if (len < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    buffer[len] = '\0';  // Null-terminate the received data

    // Print server's response
    printf("Server response: %s\n", buffer);

    // Close socket
    close(sockfd);

    return 0;
}

