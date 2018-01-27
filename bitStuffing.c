#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FLAG "01111110"

void sender();
void reciever(char* msg);

void main()
{
	sender();
}

void sender()
{
	printf("Enter the frame bits : ");
	char data[200], msg[256];
	scanf("%s", data);

	strcpy(msg, FLAG);
	int count = 0, i, j;
	for( i = strlen(msg), j = 0; data[j] != '\0'; i++, j++)
	{
		msg[i] = data[j];
		if(msg[i] == '1')
			count++;
		if(count == 5)
		{
			msg[++i] = '0';
			count = 0;
		}
	}
	msg[i] = '\0';
	strcat(msg, FLAG );
	printf("Sent msg : %s \n", msg);
	reciever(msg);
}

void reciever(char* msg)
	{
	char data[256], bit;
	int count = 0, i, j;
	
	msg = strstr(msg, FLAG) + strlen(FLAG);
	*(strstr(msg, FLAG)) = '\0';
	
	for( i = 0, j = 0; msg[i] != '\0'; i++, j++)
	{
		data[j] = msg[i];
		if(msg[i] == '1')
				count++;
		if(count == 5 && ( msg[i+1] == '0'))
		{
			i++;
			count = 0;
		}
	}
	data[j] = '\0';
	printf("Decoded data : %s \n", data);
}
