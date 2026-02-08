// CMSC 130 - Logic Design and Digital Computer Circuits
// Fernando D. Alcantara Jr.
// 1st Year - BS Computer Science
// Created: February 07, 2026

// header files
#include <stdio.h>
#include <string.h> //For string length na ininput ng user
#include <ctype.h>	//I utilized this for toupper in Hexadecimal

// other functions below ng main
int inputBinary();
int inputOctal();
int inputDecimal();
int inputHexadecimal();
int inputBCD();
int toBinary(int num);
int toOctal(int num);
int toDecimal(int num);
int toHexadecimal(int num);
void toBCD(int num);
void displayConversions(int decimalNum, int convert);
void exitProgram();
void displayMenuAndGetInput(int *mode, int *convert);

// global declaration ng mga variables
int num;
int arr[32]; // storage para sa binary number
int i = 0;	 // counter
int j = 0;	 // counter din for the remainder

// main function
int main()
{
	int mode;
	int convert;
	int continueProgram = 1;

	while (continueProgram)
	{
		displayMenuAndGetInput(&mode, &convert);

		if (mode == 6 || convert == 7)
		{
			exitProgram();
			continueProgram = 0;
			continue;
		}

		int decimal = -1;
		switch (mode)
		{
		case 1:
			decimal = inputBinary();
			break;
		case 2:
			decimal = inputOctal();
			break;
		case 3:
			decimal = inputDecimal();
			break;
		case 4:
			decimal = inputHexadecimal();
			break;
		case 5:
			decimal = inputBCD();
			break;
		}

		if (decimal >= 0)
		{
			displayConversions(decimal, convert);
		}
	}

	return 0;
} // end of main

// Functions for the input ng mga numbers
int inputBinary()
{
	char binaryNum[100];
	int decimal = 0;
	int isValid = 0;
	int len;
	int power = 1;

	printf("\n--- BINARY INPUT MODE ---\n");
	printf("Enter a binary number (0s and 1s only): ");

	// Keep asking until valid binary input since 0 at 1 lang pwede
	while (!isValid)
	{
		scanf("%s", binaryNum);
		len = strlen(binaryNum);
		isValid = 1;

		for (i = 0; i < len; i++)
		{
			if (binaryNum[i] != '0' && binaryNum[i] != '1')
			{
				isValid = 0;
				printf("Invalid binary number. Only 0s and 1s allowed.\n");
				printf("Enter a binary number: ");
				break;
			}
		}
	}

	for (i = len - 1; i >= 0; i--)
	{
		if (binaryNum[i] == '1')
		{
			decimal += power;
		}
		power *= 2;
	}

	printf("\nBinary Input: %s\n", binaryNum);
	return decimal;
}

int inputOctal()
{
	char octalNum[100];
	int isValid = 0;
	int decimal = 0;
	int len;
	int power = 1;
	int digit;

	printf("\n--- OCTAL INPUT MODE ---\n");
	printf("Enter an octal number (0-7 only): ");

	while (!isValid)
	{
		scanf("%s", octalNum);
		len = strlen(octalNum);
		isValid = 1;

		// 0 to 7 lang pwede
		for (i = 0; i < len; i++)
		{
			if (octalNum[i] < '0' || octalNum[i] > '7')
			{
				isValid = 0;
				printf("Invalid octal number. Only digits 0-7 allowed.\n");
				printf("Enter an octal number: ");
				break;
			}
		}
	}

	for (i = len - 1; i >= 0; i--)
	{
		digit = octalNum[i] - '0'; // conver ng char to int
		decimal += digit * power;
		power *= 8;
	}

	printf("\nOctal Input: %s\n", octalNum);
	return decimal;
}

int inputDecimal()
{
	int decimal;

	printf("\n--- DECIMAL INPUT MODE ---\n");
	printf("Enter a decimal number: ");
	scanf("%d", &decimal);

	printf("\nDecimal Input: %d\n", decimal);
	return decimal;
}

int inputHexadecimal()
{
	char hexNum[100];
	int decimal = 0;
	int isValid = 0;
	int len;
	int power = 1;
	int digit;

	printf("\n--- HEXADECIMAL INPUT MODE ---\n");
	printf("Enter a hexadecimal number (0-9, A-F only): ");

	while (!isValid)
	{
		scanf("%s", hexNum);
		len = strlen(hexNum);
		isValid = 1;

		// Check each character dapat 0-9 and A-F lang
		for (i = 0; i < len; i++)
		{
			char c = toupper(hexNum[i]); // convert to uppercase for checking (dito ginamit ang ctype)
			if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
			{
				isValid = 0;
				printf("Invalid hexadecimal number. Only 0-9 and A-F are allowed.\n");
				printf("Enter a hexadecimal number: ");
				break;
			}
		}
	}

	for (i = len - 1; i >= 0; i--)
	{
		char c = toupper(hexNum[i]); // convert to uppercase
		if (c >= '0' && c <= '9')
		{
			digit = c - '0'; // string to int conversion
		}
		else
		{
			digit = c - 'A' + 10;
		}
		decimal += digit * power;
		power *= 16;
	}

	printf("\nHexadecimal Input: %s\n", hexNum);
	return decimal;
}

int inputBCD()
{
	char bcdNum[200];
	int decimal = 0;
	int isValid = 0;
	int len;
	int digit;

	printf("\n--- BCD INPUT MODE ---\n");
	printf("Enter BCD (groups of 4 bits, e.g. 00010010 for 12): ");

	while (!isValid)
	{
		scanf("%s", bcdNum);
		len = strlen(bcdNum);
		isValid = 1;

		// Length must be multiple of 4
		if (len % 4 != 0)
		{
			isValid = 0;
			printf("Invalid BCD. Length must be multiple of 4 (e.g. 0001, 00010010).\n");
			printf("Enter BCD: ");
			continue;
		}

		// Each 4-bit group must be 0000-1001 (0-9)
		for (i = 0; i < len; i += 4)
		{
			digit = 0;
			for (j = 0; j < 4; j++)
			{
				if (bcdNum[i + j] != '0' && bcdNum[i + j] != '1')
				{
					isValid = 0;
					printf("Invalid BCD. Only 0s and 1s allowed.\n");
					printf("Enter BCD: ");
					break;
				}
				digit = digit * 2 + (bcdNum[i + j] - '0');
			}
			if (!isValid)
				break;
			if (digit > 9)
			{
				isValid = 0;
				printf("Invalid BCD. Each 4-bit group must be 0000-1001 (0-9).\n");
				printf("Enter BCD: ");
				break;
			}
			decimal = decimal * 10 + digit;
		}
	}

	printf("\nBCD Input: %s\n", bcdNum);
	return decimal;
}

int toBinary(int num)
{
	int isNegative = 0;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("Binary: 0");
		return 0;
	}

	i = 0;
	while (num > 0)
	{
		arr[i] = num % 2;
		num = num / 2;
		i++;
	}

	printf("Binary: ");
	if (isNegative)
		printf("-");

	for (j = i - 1; j >= 0; j--)
	{
		printf("%d", arr[j]);
	}

	return 0;
}

int toOctal(int num)
{
	int isNegative = 0;
	int octalArr[32];
	int k = 0;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("Octal: 0");
		return 0;
	}

	while (num > 0)
	{
		octalArr[k] = num % 8;
		num = num / 8;
		k++;
	}

	printf("Octal: ");
	if (isNegative)
		printf("-");
	for (j = k - 1; j >= 0; j--)
		printf("%d", octalArr[j]);
	return 0;
}

int toDecimal(int num)
{
	printf("Decimal: %d", num);
	return 0;
}

int toHexadecimal(int num)
{
	int isNegative = 0;
	int hexArr[32];
	int k = 0;
	char hexChars[] = "0123456789ABCDEF"; // characters for hex digits

	if (num < 0)
	{
		isNegative = 1;
		num = -num; // make it positive
	}

	if (num == 0)
	{
		printf("Hexadecimal: 0");
		return 0;
	}

	while (num > 0)
	{
		hexArr[k] = num % 16;
		num = num / 16;
		k++;
	}

	printf("Hexadecimal: ");
	if (isNegative)
		printf("-");

	for (j = k - 1; j >= 0; j--)
	{
		printf("%c", hexChars[hexArr[j]]);
	}

	return 0;
}

void toBCD(int num)
{
	int isNegative = 0;
	int digits[12];
	int numDigits = 0;
	int d;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("BCD: 0000");
		return;
	}

	// Extract decimal digits (reverse order)
	while (num > 0)
	{
		digits[numDigits++] = num % 10;
		num = num / 10;
	}

	printf("BCD: ");
	if (isNegative)
		printf("-");

	// Convert each digit to 4-bit BCD (print from most significant)
	for (j = numDigits - 1; j >= 0; j--)
	{
		d = digits[j];
		printf("%d%d%d%d", (d >> 3) & 1, (d >> 2) & 1, (d >> 1) & 1, d & 1);
	}
}

// para idisplay based on convert selection
void displayConversions(int decimalNum, int convert)
{
	printf("\n--- CONVERSION RESULTS ---\n");
	switch (convert)
	{
	case 1:
		toBinary(decimalNum);
		break;
	case 2:
		toOctal(decimalNum);
		break;
	case 3:
		toDecimal(decimalNum);
		break;
	case 4:
		toHexadecimal(decimalNum);
		break;
	case 5:
		toBCD(decimalNum);
		break;
	case 6:
		toBinary(decimalNum);
		printf("\n");
		toOctal(decimalNum);
		printf("\n");
		toDecimal(decimalNum);
		printf("\n");
		toHexadecimal(decimalNum);
		printf("\n");
		toBCD(decimalNum);
		break;
	}
	printf("\n");
}

void exitProgram()
{
	printf("\nProgram terminated.\n\n");
	return;
}

void displayMenuAndGetInput(int *mode, int *convert)
{
	// Hero Section ng PROGRAM
	printf("\n\n--- NUMBER SYSTEM CONVERTER ---\n\n");
	printf("What do you want to input: \n");
	printf("[1] Binary (base 2)\n");
	printf("[2] Octal (base 8)\n");
	printf("[3] Decimal (base 10)\n");
	printf("[4] Hexadecimal (base 16) \n");
	printf("[5] Binary-Coded Decimal \n");
	printf("[6] EXIT THE PROGRAM \n\n");

	// Input validation loop ng number
	do
	{
		printf("Please select a number system to input: ");
		scanf("%d", mode);
		if (*mode < 1 || *mode > 6)
		{
			printf("Invalid input. Please select from 1 to 6 only\n");
		}
	} while (*mode < 1 || *mode > 6);

	// Saan icoconvert
	printf("\n\nConvert to: \n");
	printf("[1] Binary (base 2)\n");
	printf("[2] Octal (base 8)\n");
	printf("[3] Decimal (base 10)\n");
	printf("[4] Hexadecimal (base 16) \n");
	printf("[5] Binary-Coded Decimal \n");
	printf("[6] All \n");
	printf("[7] EXIT THE PROGRAM \n\n");

	do
	{
		printf("Please select a number system to convert to: ");
		scanf("%d", convert);
		if (*convert < 1 || *convert > 7)
		{
			printf("Invalid input. Please select from 1 to 7 only\n");
		}
	} while (*convert < 1 || *convert > 7);
}