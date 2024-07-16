#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 16661
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[BUF_SIZE];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind socket to server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Receive message from client
        int len = recvfrom(sockfd, (char *)buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (len < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }
        buffer[len] = '\0';  // Null-terminate the received data

        // Print client's IP and message
        printf("Message from client %s:%d - %s\n", 
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Echo back to client
        sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&client_addr, addr_len);
    }

    // Close socket
    close(sockfd);

    return 0;
}

