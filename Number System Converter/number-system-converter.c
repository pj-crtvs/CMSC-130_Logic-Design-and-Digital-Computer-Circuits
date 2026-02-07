// CMSC 130 - Logic Design and Digital Computer Circuits
// Fernando D. Alcantara Jr.
// 1st Year - BS Computer Science
// Created: February 07, 2026

// header files
#include <stdio.h>

// other functions

// main function
int main()
{
	printf("\n\n--NUMBER SYSTEM CONVERTER--\n\n");
	printf("[1] Binary (base 2)\n");
	printf("[2] Octal (base 8)\n");
	printf("[3] Decimal (base 10)\n");
	printf("[4] Hexadecimal (base 16) \n\n");
	printf("Please select a number system to input: ");

	printf("");
	

	int num;	 // decimal number to be provided by the user
	int arr[32]; // storage for the binary number
	int i = 0;	 // counter
	int j = 0;	 // counter din for the remainder

	printf("Please enter a number:");
	scanf("%d", &num);

	if (num == 0)
	{
		printf("Binary is 0.");
	}

	for (i = 0; num > 0; i++)
	{
		arr[i] = num % 2;
		num = num / 2;
	}

	printf("The binary number is: ");
	for (j = i - 1; j >= 0; j--)
	{
		printf("%d", arr[j]);
	}

	return 0;
}
