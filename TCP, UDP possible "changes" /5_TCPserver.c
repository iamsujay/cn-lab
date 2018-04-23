// 2 way communication

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

	struct sockaddr_in cliAddr;
	int cliSize;
	int inSock = accept(servSock, (struct sockaddr*)&cliAddr, &cliSize);

	char buf[1024];
	read(inSock, &buf, sizeof(buf));
	printf("Recieved from client : %s\n", buf);

	int clientSock = socket(AF_INET, SOCK_STREAM, 0);
	connect(clientSock, (struct sockaddr*) &cliAddr, cliSize);
	write( clientSock, buf, strlen(buf)); 	// modify buf here, if required

}
