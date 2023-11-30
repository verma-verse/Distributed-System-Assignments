// Purva Gautam
// 20184014
// CS-7B

#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// make all vowels upper case
void upper_vowel_case(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' ||
			str[i] == 'u')
		{
			str[i] = toupper(str[i]);
		}
		i++;
	}
}

int main()
{
	int fd = 0;
	char buff[1024];
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
	server.sin_port = htons(10011);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(fd, (struct sockaddr *)&server, sizeof(server));
	int in;
	listen(fd, 10);
	while (in = accept(fd, (struct sockaddr *)NULL, NULL))
	{
		int childpid, n;
		if ((childpid = fork()) == 0)
		{
			close(fd);
			bzero(buff, 256);
			while ((n = recv(in, buff, 256, 0)) > 0)
			{
				printf("\nServer Received: %s", buff);
				upper_vowel_case(buff);
				send(in, buff, strlen(buff), 0);
				bzero(buff, 256);
			}
			close(in);
			exit(0);
		}
	}
}
