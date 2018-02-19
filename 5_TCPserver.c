#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define PORT 7892

void main()
{
	struct sockaddr_in servAddr;
	servAddr.sin_family	= AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(PORT);

	int servSock = socket(AF_INET, SOCK_STREAM, 0);
	bind(servSock,(struct sockaddr*) &servAddr, sizeof(servAddr));
	listen(servSock,5);
	int inSock = accept(servSock, NULL, NULL);

	char buf[1024];
	read(inSock, &buf, sizeof(buf));
	write(1,buf,strlen(buf));
}
