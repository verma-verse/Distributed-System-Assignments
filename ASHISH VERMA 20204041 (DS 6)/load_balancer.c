// ASHISH VERMA 20204041
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER1_PORT 8888
#define SERVER2_PORT 8889

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int server1_socket, server2_socket, client_socket;
    struct sockaddr_in server1_addr, server2_addr, client_addr;
    socklen_t clilen = sizeof(client_addr);

    // Create sockets for the two servers
    server1_socket = socket(AF_INET, SOCK_STREAM, 0);
    server2_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server1_socket < 0 || server2_socket < 0) {
        error("Error opening server socket");
    }

    // Define server addresses
    memset(&server1_addr, 0, sizeof(server1_addr));
    server1_addr.sin_family = AF_INET;
    server1_addr.sin_port = htons(SERVER1_PORT);
    server1_addr.sin_addr.s_addr = INADDR_ANY;

    memset(&server2_addr, 0, sizeof(server2_addr));
    server2_addr.sin_family = AF_INET;
    server2_addr.sin_port = htons(SERVER2_PORT);
    server2_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind servers to their respective ports
    if (bind(server1_socket, (struct sockaddr *)&server1_addr, sizeof(server1_addr) < 0) ||
        bind(server2_socket, (struct sockaddr *)&server2_addr, sizeof(server2_addr) < 0) {
        error("Error binding server socket");
    }

    // Listen for connections on both servers
    listen(server1_socket, 5);
    listen(server2_socket, 5);

    // Accept client connections and distribute load
    while (1) {
        client_socket = accept(server1_socket, (struct sockaddr *)&client_addr, &clilen);
        if (client_socket < 0) {
            error("Error accepting client connection");
        }

        // Check CPU utilization and select the server with lower utilization (implement this logic)

        // For simplicity, assume server1 has lower utilization here
        int selected_server_socket = server1_socket;

        // Forward the client request to the selected server
        // Implement this part: read from client_socket, and write to selected_server_socket

        // Read from the server and send the response back to the client

        // Close the client_socket after the request is processed
        close(client_socket);
    }

    close(server1_socket);
    close(server2_socket);

    return 0;
}
