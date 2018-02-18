#include <stdio.h>
#include <string.h>

void sender(int n);
void reciever(char* data);

void main()
{
	int n, i;
	printf("Number of data bytes : ");
	scanf("%d", &n);
	sender(n);
}

void sender(int n)
{
	int i;
	char buffer[9], msg[10];
	for(i = 0; i < n; i++)
	{
		printf("Frame-%d : ", i);
		scanf("%s", buffer);
		sprintf(msg, "%d%s", strlen(buffer), buffer);
		reciever(msg);
	}
}

void reciever(char* msg)
{
	int lenStated = msg[0] - '0', lenRecieved = strlen( msg );
	printf("Recieved : %s\n", msg);
	printf("length : stated = %d, recieved = %d \n", lenStated, lenRecieved);
}