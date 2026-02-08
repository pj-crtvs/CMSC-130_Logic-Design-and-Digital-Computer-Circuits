// CMSC 130 - Logic Design and Digital Computer Circuits
// Decimal to Binary, Octal, Hexadecimal, BCD Converter
// Fernando D. Alcantara Jr.
// 1st Year - BS Computer Science

// Header files
#include <stdio.h>
#include <string.h> // for buffer input
#include <ctype.h>	// for sscanf (from string to int)

// Function prototypes; written after ng main function
int getValidInt(void);
void toBinary(int num);
void toOctal(int num);
void toHexadecimal(int num);
void toBCD(int num);
void displayAllConversions(int num);
void displayConversion(int num, int choice);

// start of main functin
int main()
{
	int decimal;
	int choice;
	int running = 1;

	// loop the program until ma-exit ng user
	while (running)
	{
		// index interface ng program
		printf("\n\n--- DECIMAL NUMBER SYSTEM CONVERTER ---\n\n");
		printf("Convert to:\n");
		printf("[1] Binary (base 2)\n");
		printf("[2] Octal (base 8)\n");
		printf("[3] Hexadecimal (base 16)\n");
		printf("[4] Binary-Coded Decimal (BCD)\n");
		printf("[5] All\n");
		printf("[6] EXIT\n\n");

		printf("Input convert decimal to:  ");
		choice = getValidInt();

		// choice validation
		if (choice < 1 || choice > 6)
		{
			printf("Invalid choice. Select only from 1 to 6.\n");
			continue;
		}

		// exit the program
		if (choice == 6)
		{
			printf("program terminated.\n");
			break;
		}

		printf("Input decimal number: ");
		decimal = getValidInt();

		printf("You entered: %d\n", decimal);
		displayConversion(decimal, choice);
	}

	return 0;
} // end of main

// Validation ng integer input from the user; This is base from the C repository on how to get a valid int
int getValidInt(void)
{
	char buffer[256];
	int value;
	char *p;

	while (1)
	{
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			printf("Failed to read input.\n");
			continue;
		}

		// Remove newline sa input
		buffer[strcspn(buffer, "\n")] = '\0';

		p = buffer;
		while (*p == ' ' || *p == '\t') // spaces or tabss
			p++;

		// since null ang huli ng string, if hindi nagenter lang si user, null ang ang meron so:
		if (*p == '\0')
		{
			printf("Empty input. Enter an integer only.\n");
			continue;
		}

		// Validate digits only, optional lang ang + or -
		char *check = p;
		if (*check == '+' || *check == '-')
			check++;
		while (*check != '\0')
		{
			if (!isdigit((unsigned char)*check))
			{
				printf("Invalid input. Only integers allowed (0-9, optional: + or -).\n");
				break;
			}
			check++;
		}
		if (*check != '\0')
			continue;

		if (sscanf(p, "%d", &value) != 1)
		{
			printf("Invalid integer format.\n");
			continue;
		}

		return value;
	}
}

// COVERSION FUNCTIONS
// for binary
void toBinary(int num)
{
	int arr[32];
	int k = 0;
	int j;
	int isNegative = 0;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("Binary: 0");
		return;
	}

	while (num > 0)
	{
		arr[k++] = num % 2;
		num = num / 2;
	}

	printf("Binary: ");
	if (isNegative)
		printf("-");
	for (j = k - 1; j >= 0; j--)
		printf("%d", arr[j]);
}

// for octal
void toOctal(int num)
{
	int arr[32];
	int k = 0;
	int j;
	int isNegative = 0;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("Octal: 0");
		return;
	}

	while (num > 0)
	{
		arr[k++] = num % 8;
		num = num / 8;
	}

	printf("Octal: ");
	if (isNegative)
		printf("-");
	for (j = k - 1; j >= 0; j--)
		printf("%d", arr[j]);
}

// for hexa
void toHexadecimal(int num)
{
	int arr[32];
	int k = 0;
	int j;
	int isNegative = 0;
	char hexChars[] = "0123456789ABCDEF";

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	if (num == 0)
	{
		printf("Hexadecimal: 0");
		return;
	}

	while (num > 0)
	{
		arr[k++] = num % 16;
		num = num / 16;
	}

	printf("Hexadecimal: ");
	if (isNegative)
		printf("-");
	for (j = k - 1; j >= 0; j--)
		printf("%c", hexChars[arr[j]]);
}

// for BCD
void toBCD(int num)
{
	int digits[12];
	int numDigits = 0;
	int j, d;
	int isNegative = 0;

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

	while (num > 0)
	{
		digits[numDigits++] = num % 10;
		num = num / 10;
	}

	printf("BCD: ");
	if (isNegative)
		printf("-");
	for (j = numDigits - 1; j >= 0; j--)
	{
		d = digits[j];
		printf(" %d%d%d%d", (d >> 3) & 1, (d >> 2) & 1, (d >> 1) & 1, d & 1);
		// utilized right shift since kada digit may represntation an 4 bit binary.
		// Right shift bawat number sa binary to para makuha ang Least significant bit thru "& 1"
	}
}

// DISPLAYING FUNCTIONS
// display ang selected conversion
void displayConversion(int num, int choice)
{
	printf("\n--- CONVERSION RESULTS ---\n");
	switch (choice)
	{
	case 1:
		toBinary(num);
		break;
	case 2:
		toOctal(num);
		break;
	case 3:
		toHexadecimal(num);
		break;
	case 4:
		toBCD(num);
		break;
	case 5:
		displayAllConversions(num);
		break;
	}
	printf("\n");
}

// display all conversionS
void displayAllConversions(int num)
{
	toBinary(num);
	printf("\n");
	toOctal(num);
	printf("\n");
	toHexadecimal(num);
	printf("\n");
	toBCD(num);
}