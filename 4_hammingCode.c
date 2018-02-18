#include <stdio.h>

void sender(int* data);
void reciever();

void main()
{
    char input[4];
    printf("Enter the 4-bit data : ");
    scanf("%s", input);

    int data[4+3], i;
    for(i = 0; i <4; i++)
            data[i] = input[i] - '0';
    sender(data);
}

void sender(int* data)
{
    int a3, a2, a1, a0, r2, r1, r0;
    a3 = data[0];
    a2 = data[1];
    a1 = data[2];
    a0 = data[3];

    r0 = a0 ^ a1 ^ a2;
    r1 = a1 ^ a2 ^ a3;
    r2 = a3 ^ a0 ^ a1;

    data[4] = r2;
    data[5] = r1;
    data[6] = r0;

    int i;
    printf("Data to send : ");
    for(i=0; i<7; i++)
            printf("%d", data[i]);

    reciever();
}

void reciever()
{       
    char input[7];
    printf("\nData to recieve : ");
    scanf("%s", input);
    int data[7], i;
    for(i = 0; i <7; i++)
        data[i] = input[i] - '0';

    int b3, b2, b1, b0, q2, q1, q0, s2, s1, s0;
    b3 = data[0];
    b2 = data[1];
    b1 = data[2];
    b0 = data[3];
    q2 = data[4];
    q1 = data[5];
    q0 = data[6];

    s0 = b0 ^ b1 ^ b2 ^ q0;
    s1 = b1 ^ b2 ^ b3 ^ q1;
    s2 = b3 ^ b0 ^ b1 ^ q2;

    // represent syndrome in 3-bit binary
    int syndrome = s0 + (s1 * 10) + (s2 * 100);
    int pos;
    switch(syndrome)
    {
        case(0) :   pos = -1;
                    break;
        case(1) :   pos = 7;
                    break;
        case(10) :  pos = 6;
                    break;
        case(11) :  pos = 2;
                    break;
        case(100) : pos = 5;
                    break;
        case(101) : pos = 4;
                    break;
        case(110) : pos = 1;
                    break;
        case(111) : pos = 3;
                    break;
    }
    if(pos == -1 )
        printf("Error free\n");
    else
    {
        printf("Error detected at bit %d \n", pos);
        data[pos-1] = !(data[pos-1]);
        printf("Corrected data : ");
        for(i = 0; i <7; i++)
            printf("%d", data[i]);
        printf("\n");
    }
}

