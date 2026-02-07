// This is a program that converts decimal to binary
//
// CMSC 130 
// DMCS
//
// Created: February 5, 2026
//
//


// header files
#include <stdio.h>


int main()
{
	int num; // decimal number to be provided by the user
	int arr[32]; // storage for the binary number
	int i=0; // counter 
	int j=0; // counter din for the remainder

	printf("Please enter a number:");
	scanf("%d", &num);

	if(num == 0)
	{
		printf("Binary is 0.");
	}
	
	for (i=0; num>0; i++)
	{
		arr[i]= num % 2; 
		num = num/2;
	}

	printf("The binary number is: ");
	for(j=i-1; j>=0; j--)
	{
		printf("%d", arr[j]);
	}

	return 0;
}
