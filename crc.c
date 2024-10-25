#include <stdio.h>
#include <string.h>

// Length of the generator polynomial
#define N strlen(gen_poly)

// Data and CRC check values
char data[28], check_value[28], gen_poly[10];
int data_length, i, j;

// Perform XOR operation based on generator polynomial
void XOR()
{
    for (j = 1; j < N; j++)
        check_value[j] = (check_value[j] == gen_poly[j]) ? '0' : '1';
}

// Perform CRC calculation to check for errors
void crc()
{
    // Initialize check_value with the data
    for (i = 0; i < N; i++)
        check_value[i] = data[i];

    // Perform CRC division process
    for (i = N; i <= data_length + N - 1; i++)
    {
        // If the first bit is 1, XOR with the generator polynomial
        if (check_value[0] == '1')
            XOR();

        // Shift bits left by one position
        for (j = 0; j < N - 1; j++)
            check_value[j] = check_value[j + 1];

        // Append the next bit of data
        check_value[j] = data[i];
    }
}

// Simulate receiver to check for transmission errors
void receiver()
{
    printf("Enter the received data: ");
    scanf("%s", data);
    printf("\nData received: %s", data);

    crc(); // Recalculate CRC on received data

    // Check for errors by verifying if all bits in check_value are zero
    for (i = 0; (i < N - 1) && (check_value[i] != '1'); i++)
        ;
    if (i < N - 1)
        printf("\nError detected\n");
    else
        printf("\nNo error detected\n");
}

int main()
{
    // Get the data to be transmitted and generator polynomial
    printf("Enter data to be transmitted: ");
    scanf("%s", data);
    printf("Enter the generating polynomial: ");
    scanf("%s", gen_poly);

    data_length = strlen(data);

    // Append n-1 zeros to the data to reserve space for CRC
    for (i = data_length; i < data_length + N - 1; i++)
        data[i] = '0';

    printf("\nData padded with zeros: %s", data);

    crc(); // Calculate CRC for the data

    printf("\nCRC (Check value) is: %s", check_value);

    // Append CRC to data for final transmission
    for (i = data_length; i < data_length + N - 1; i++)
        data[i] = check_value[i - data_length];
    printf("\nFinal data to be sent: %s\n", data);

    receiver(); // Check for errors at receiver end
    return 0;
}
