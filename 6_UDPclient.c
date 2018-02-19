#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 7892

void main()
{
	int newSocket = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in servAddr;
	servAddr.sin_family	= AF_INET;
	servAddr.sin_port 	= htons(PORT);
	inet_pton(AF_INET,"127.0.0.1",&servAddr.sin_addr);

	char buf[1024];
	printf("Message : ");
	fgets(buf, sizeof(buf), stdin);
	sendto(newSocket, buf, strlen(buf), 0, (struct sockaddr*) &servAddr, sizeof(servAddr));
  }
