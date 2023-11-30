// ASHISH VERMA 20204041
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_ADDRESS "127.0.0.1"  // The IP address of the load balancer
#define SERVER_PORT 8888

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[256];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error opening client socket");
        exit(1);
    }

    // Define the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    // Connect to the load balancer
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr) < 0) {
        perror("Error connecting to load balancer");
        close(client_socket);
        exit(1);
    }

    // Send a message to the load balancer
    strcpy(message, "hello");
    send(client_socket, message, strlen(message), 0);

    // Receive and print the response from the load balancer
    bzero(message, 256);
    recv(client_socket, message, 255, 0);
    printf("Received: %s\n", message);

    // Close the client socket
    close(client_socket);

    return 0;
}
