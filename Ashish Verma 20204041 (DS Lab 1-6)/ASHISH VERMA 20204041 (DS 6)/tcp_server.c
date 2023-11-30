// ASHISH VERMA 20204041
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

char *toUpperCase(char *str)
{
    // Implement your logic to convert the string to uppercase
    // For simplicity, we are using the standard library function here
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen = sizeof(client_addr);

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        error("Error opening server socket");
    }

    // Define server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the server to the port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr) < 0) {
        error("Error binding server socket");
    }

    // Listen for incoming connections
    listen(server_socket, 5);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &clilen);
        if (client_socket < 0)
        {
            error("Error accepting client connection");
        }

        // Read the lowercase string from the client
        char buffer[256];
        bzero(buffer, 256);
        int n = read(client_socket, buffer, 255);
        if (n < 0)
        {
            error("Error reading from client");
        }

        // Convert the string to uppercase
        char *result = toUpperCase(buffer);

        // Send the uppercase string back to the client
        n = write(client_socket, result, strlen(result));
        if (n < 0)
        {
            error("Error writing to client");
        }

        // Close the client socket
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
