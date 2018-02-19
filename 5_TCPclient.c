#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 7892

void main()
{
	struct sockaddr_in servAddr;
	servAddr.sin_family	= AF_INET;
	servAddr.sin_port 	= htons(PORT);
	inet_pton(AF_INET,"127.0.0.1", &servAddr.sin_addr);

	int clientSock = socket(AF_INET, SOCK_STREAM, 0);
	connect(clientSock, (struct sockaddr*) &servAddr, sizeof(servAddr));

	char buf[1024];
	printf("Message : ");
	fgets(buf,sizeof(buf),stdin);
	send(clientSock, buf, strlen(buf), 0);
  }
