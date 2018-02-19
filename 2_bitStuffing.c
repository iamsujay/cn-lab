/* dataframe is a string of bits with FLAG at both ends
 * sender()   - add a 0 in msg after five 1's in data
 * reciever() - remove 0 for data after five 1's in msg
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FLAG "01111110"
#define SIZE 200

void sender(char* data);
void reciever(char* msg);

void main()
{
	char data[SIZE];
	printf("Enter the frame bits : ");
	scanf("%s", data);
	sender(data);
}

void sender(char* data)
{
	char msg[SIZE + 40];
	strcpy(msg, FLAG);				// message to start with FLAG
	int oneCount = 0, i, j;			
	for(i=0, j=strlen(msg); data[i]!= '\0'; msg[j++] = data[i++])
	{
		if(oneCount == 5)
		{
			msg[j++] = '0';					
			oneCount = 0;
		}
		if(data[i] == '1')
			oneCount++;
		else
			oneCount = 0;
	}
	strcpy(msg+j, FLAG );			// message to end with FLAG
	printf("Sent msg : %s \n", msg);
	reciever(msg);
}

void reciever(char* msg)
{
	msg = strstr(msg, FLAG) + strlen(FLAG); 	// fwd begining FLAG
	*(strstr(msg, FLAG)) = '\0'; 				// trim ending FLAG

	char data[SIZE];
	int oneCount = 0, i, j;
	for(i=0, j=0; msg[i] != '\0'; data[j++] = msg[i++] )
	{
		if((oneCount == 5) && (msg[i] == '0'))
		{
			++i;
			oneCount = 0;
		}
		if(msg[i] == '1')
			oneCount++;
		else
			oneCount = 0;
	}
	data[j] = '\0';
	printf("Decoded data : %s \n", data);
}
