// Purva Gautam
// 20184014
// CS-7B


#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int fd = 0;
    char buff[1024];
    if (argc < 3)
    {
        printf("Less no of arguments !!");
        return 0;
    }
    memset(buff, '0', sizeof(buff));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Client Error: Socket not created succesfully");
        return 0;
    }
    struct sockaddr_in server;
    memset(&server, '0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    int in = inet_pton(AF_INET, argv[1], &server.sin_addr);
    if (in < 0)
    {
        perror("Client Error: IP not initialized succesfully");
        return 0;
    }
    in = connect(fd, (struct sockaddr *)&server, sizeof(server));
    if (in < 0)
    {
        perror("Client Error: Connection Failed.");
        return 0;
    }
    while (1)
    {
        printf("\nPlease enter the string: ");
        bzero(buff, 256);
        fgets(buff, 255, stdin);
        printf("\nSending string to SERVER: %s ", buff); /* Send message to the server */
        in = send(fd, buff, strlen(buff), 0);
        if (in < 0)
        {
            perror("\nClient Error: Writing to Server");
            return 0;
        }
        bzero(buff, 256);

        in = recv(fd, buff, 255, 0);
        if (in < 0)
        {
            perror("\nClient Error: Reading from Server");
            return 0;
        }
        printf("\nReceived FROM SERVER: %s ", buff);
    }
    printf("BYE!\n");
    close(fd);
    return 0;
}
