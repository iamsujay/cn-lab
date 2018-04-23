#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PORT 7892

void main()
{
	int servSock = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in servAddr;
	servAddr.sin_family 	 = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port 	 = htons(PORT);

	bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr));
	
	char buf[1024];
	struct sockaddr_in cliAddr;
	int cliSize;
	while(1)
	{
		recvfrom(servSock, &buf, sizeof(buf), 0, (struct sockaddr*)&cliAddr, &cliSize);
		sendto(servSock, buf, strlen(buf)+1, 0, (struct sockaddr*)&cliAddr, cliSize);
		if(strcmp(buf, "exit") == 0)
			break;
		printf("%s\n", buf);
	};
}
