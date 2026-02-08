// CMSC 130 - Logic Design and Digital Computer Circuits
// Decimal to Binary, Octal, Hexadecimal, BCD Converter
// Fernando D. Alcantara Jr.
// 1st Year - BS Computer Science

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes na ginamit ko after ng main function
int getMenuChoice(int *outChoice);
int getDecimalInput(int *outValue);
void toBinary(int num);
void toOctal(int num);
void toHexadecimal(int num);
void toBCD(int num);
void displayAllConversions(int num);
void displayConversion(int num, int choice);

//start of main functin
int main()
{
	int decimal;
	int choice;
	int running = 1;

	//loop the program until ma-exit ng user
	while (running)
	{
		printf("\n\n--- DECIMAL NUMBER SYSTEM CONVERTER ---\n\n");
		printf("Convert to:\n");
		printf("[1] Binary (base 2)\n");
		printf("[2] Octal (base 8)\n");
		printf("[3] Hexadecimal (base 16)\n");
		printf("[4] Binary-Coded Decimal (BCD)\n");
		printf("[5] All\n");
		printf("[6] EXIT\n\n");

		// get the choice kung ano ang conversion na gusto ni user 
		do
		{
			printf("Select option (1-6): ");
			if (!getMenuChoice(&choice))
			{
				printf("Invalid input. Enter a number (1-6) only.\n");
			}
			else if (choice < 1 || choice > 6)
			{
				printf("Please select from 1 to 6 only.\n");
			}
		} while (choice < 1 || choice > 6);

		if (choice == 6)
		{
			printf("\nProgram terminated.\n\n");
			running = 0;
			continue;
		}

		// Get decimal input with error handling
		if (!getDecimalInput(&decimal))
			continue;

		printf("\nDecimal Input: %d\n", decimal);
		displayConversion(decimal, choice);
	}

	return 0;
}

// Gets menu choice (1-6) using fgets for consistent input
int getMenuChoice(int *outChoice)
{
	char buffer[64];
	int value;

	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		return 0;

	buffer[strcspn(buffer, "\n")] = '\0';

	char *p = buffer;
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0')
		return 0;

	if (sscanf(p, "%d", &value) != 1)
		return 0;

	*outChoice = value;
	return 1;
}

// Gets decimal input with full error handling
// Returns 1 on success (value in *outValue), 0 on error
int getDecimalInput(int *outValue)
{
	int value;
	int result;
	char buffer[256];

	printf("\nEnter a decimal number: ");

	// Read as string first for better error control
	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
		printf("Error: Failed to read input.\n");
		return 0;
	}

	// Remove newline
	buffer[strcspn(buffer, "\n")] = '\0';

	// Trim leading/trailing spaces
	char *start = buffer;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
	{
		printf("Error: Empty input. Please enter a number.\n");
		return 0;
	}

	// Validate: must be digits, optional leading + or -
	char *p = start;
	if (*p == '+' || *p == '-')
		p++;
	while (*p != '\0')
	{
		if (!isdigit((unsigned char)*p))
		{
			printf("Error: Invalid decimal. Only digits 0-9 allowed (optional + or -).\n");
			return 0;
		}
		p++;
	}

	// Convert to integer
	result = sscanf(start, "%d", &value);
	if (result != 1)
	{
		printf("Error: Invalid decimal format.\n");
		return 0;
	}

	*outValue = value;
	return 1;
}

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

void toBCD(int num)
{
	int digits[12];
	int numDigits = 0;
	int j;
	int d;
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
		printf("%d%d%d%d", (d >> 3) & 1, (d >> 2) & 1, (d >> 1) & 1, d & 1);
	}
}

//display ang selected conversion
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

//display all conversionS
void displayAllConversions(int num)
{
	toBinary(num);
	printf("\n");
	toOctal(num);
	printf("\n");
	toHexadecimal(num);
	printf("\n");
	toBCD(num);
