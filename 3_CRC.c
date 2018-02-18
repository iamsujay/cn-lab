#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COMMON_DIVISOR "1011"

char xor(char a, char b);
char* divide(char* dividend, char* divisor);
char* encode(char* data);
void decode(char* data);

void main()
{
	char data[7];
	printf("Enter 4-bit data : ");
	scanf("%s", data);
	printf("Data to send : %s\n", encode(data));

	printf("Data to recieve : ");
	scanf("%s", data);
	decode(data);
}

char xor(char a, char b)
{
	return (a==b)? '0' : '1';
}

char* divide(char* dividend, char* divisor)
{
	char rem[4];
	char *zeros = "0000";
	int i;

	while(strlen(dividend) >= strlen(divisor))
	{
		if( dividend[0] == '1')
			strcpy(rem, divisor);
		else
			strcpy(rem, zeros);

		for(i = 0; i < strlen(rem); i++)
			dividend[i] = xor(dividend[i], rem[i]);
		
		dividend++;
	}
	return dividend;
}

char* encode(char* data)
{
	char initialData[7];
	sprintf(initialData, "%s000", data);
	char* checksum = divide(initialData, COMMON_DIVISOR);

	static char encodedData[7];
	sprintf(encodedData, "%s%s", data, checksum);
	return encodedData;
}

void decode(char* data)
{
	char* checksum = divide(data, COMMON_DIVISOR);
	if(strcmp(checksum, "000") == 0)
		printf("Error-free\n");
	else
		printf("Error detected\n");
} 
