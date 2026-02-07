// CMSC 130 - Logic Design and Digital Computer Circuits
// Fernando D. Alcantara Jr.
// 1st Year - BS Computer Science
// Created: February 07, 2026

// header files
#include <stdio.h>
#include <string.h> // for string operations
#include <ctype.h>  // for character checking functions

// other functions below ng main
int inputBinary();
int inputOctal();
int inputDecimal();
int inputHexadecimal();
int toBinary(int num);
int toOctal(int num);
int toDecimal(int num);
int toHexadecimal(int num);
void exitProgram();
void displayAllConversions(int decimalNum); // displays all conversions for a decimal number

// global declaration ng variable
int num;	 // decimal number to be provided by the user
int arr[32]; // storage for the binary number
int i = 0;	 // counter
int j = 0;	 // counter din for the remainder

// main function
int main()
{
	int mode; // to select mode
	int continueProgram = 1; // flag to continue or exit

	// Main program loop - allows multiple conversions
	while (continueProgram)
	{
		// Hero Section ng PROGRAM
		printf("\n\n--NUMBER SYSTEM CONVERTER--\n\n");
		printf("[1] Binary (base 2)\n");
		printf("[2] Octal (base 8)\n");
		printf("[3] Decimal (base 10)\n");
		printf("[4] Hexadecimal (base 16) \n");
		printf("[5] EXIT THE PROGRAM \n\n");

		// Input validation loop - keeps asking until valid input (1-5)
		do
		{
			printf("Please select a number system to input: ");
			scanf("%d", &mode);
			if (mode < 1 || mode > 5)
			{
				printf("Invalid input! Please enter a number between 1 and 5.\n");
			}
		} while (mode < 1 || mode > 5);

		// Process the selected mode
		switch (mode)
		{
		case 1:
			inputBinary();
			break;
		case 2:
			inputOctal();
			break;
		case 3:
			inputDecimal();
			break;
		case 4:
			inputHexadecimal();
			break;
		case 5:
			exitProgram();
			continueProgram = 0; // exit the main loop
			break;
		}
	}

	return 0;
} // end of main

// input function with exception handling
// Converts binary input to decimal, then displays all conversions
int inputBinary()
{
	char binaryStr[100]; // store binary string input
	int decimal = 0;	   // converted decimal value
	int isValid = 0;	   // flag to check if input is valid
	int len;			   // length of binary string
	int power = 1;		   // power of 2 for conversion

	printf("\n--- BINARY INPUT MODE ---\n");
	printf("Enter a binary number (0s and 1s only): ");

	// Keep asking until valid binary input
	while (!isValid)
	{
		scanf("%s", binaryStr);
		len = strlen(binaryStr);
		isValid = 1; // assume valid first

		// Check each character - must be '0' or '1'
		for (i = 0; i < len; i++)
		{
			if (binaryStr[i] != '0' && binaryStr[i] != '1')
			{
				isValid = 0;
				printf("Invalid binary number! Only 0s and 1s allowed.\n");
				printf("Enter a binary number: ");
				break;
			}
		}
	}

	// Convert binary string to decimal
	// Start from rightmost digit (least significant bit)
	for (i = len - 1; i >= 0; i--)
	{
		if (binaryStr[i] == '1')
		{
			decimal += power; // add 2^power if bit is 1
		}
		power *= 2; // multiply by 2 for next position
	}

	printf("\nBinary Input: %s\n", binaryStr);
	displayAllConversions(decimal);

	return 0;
}

// Converts octal input to decimal, then displays all conversions
int inputOctal()
{
	char octalStr[100]; // store octal string input
	int decimal = 0;	// converted decimal value
	int isValid = 0;	// flag to check if input is valid
	int len;			// length of octal string
	int power = 1;		// power of 8 for conversion
	int digit;			// current digit value

	printf("\n--- OCTAL INPUT MODE ---\n");
	printf("Enter an octal number (0-7 only): ");

	// Keep asking until valid octal input
	while (!isValid)
	{
		scanf("%s", octalStr);
		len = strlen(octalStr);
		isValid = 1; // assume valid first

		// Check each character - must be '0' to '7'
		for (i = 0; i < len; i++)
		{
			if (octalStr[i] < '0' || octalStr[i] > '7')
			{
				isValid = 0;
				printf("Invalid octal number! Only digits 0-7 allowed.\n");
				printf("Enter an octal number: ");
				break;
			}
		}
	}

	// Convert octal string to decimal
	// Start from rightmost digit (least significant)
	for (i = len - 1; i >= 0; i--)
	{
		digit = octalStr[i] - '0'; // convert char to int
		decimal += digit * power;   // add digit * 8^power
		power *= 8;				   // multiply by 8 for next position
	}

	printf("\nOctal Input: %s\n", octalStr);
	displayAllConversions(decimal);

	return 0;
}

// Takes decimal input directly, then displays all conversions
int inputDecimal()
{
	int decimal;

	printf("\n--- DECIMAL INPUT MODE ---\n");
	printf("Enter a decimal number: ");
	scanf("%d", &decimal);

	printf("\nDecimal Input: %d\n", decimal);
	displayAllConversions(decimal);

	return 0;
}

// Converts hexadecimal input to decimal, then displays all conversions
int inputHexadecimal()
{
	char hexStr[100]; // store hexadecimal string input
	int decimal = 0;  // converted decimal value
	int isValid = 0;  // flag to check if input is valid
	int len;		  // length of hex string
	int power = 1;	  // power of 16 for conversion
	int digit;		  // current digit value

	printf("\n--- HEXADECIMAL INPUT MODE ---\n");
	printf("Enter a hexadecimal number (0-9, A-F only): ");

	// Keep asking until valid hexadecimal input
	while (!isValid)
	{
		scanf("%s", hexStr);
		len = strlen(hexStr);
		isValid = 1; // assume valid first

		// Check each character - must be 0-9 or A-F (case insensitive)
		for (i = 0; i < len; i++)
		{
			char c = toupper(hexStr[i]); // convert to uppercase for checking
			if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
			{
				isValid = 0;
				printf("Invalid hexadecimal number! Only 0-9 and A-F allowed.\n");
				printf("Enter a hexadecimal number: ");
				break;
			}
		}
	}

	// Convert hexadecimal string to decimal
	// Start from rightmost digit (least significant)
	for (i = len - 1; i >= 0; i--)
	{
		char c = toupper(hexStr[i]); // convert to uppercase
		if (c >= '0' && c <= '9')
		{
			digit = c - '0'; // convert '0'-'9' to 0-9
		}
		else
		{
			digit = c - 'A' + 10; // convert 'A'-'F' to 10-15
		}
		decimal += digit * power; // add digit * 16^power
		power *= 16;			  // multiply by 16 for next position
	}

	printf("\nHexadecimal Input: %s\n", hexStr);
	displayAllConversions(decimal);

	return 0;
}

// conversion function
// Converts decimal number to binary representation
// For negative numbers: converts absolute value and adds negative sign
int toBinary(int num)
{
	int isNegative = 0; // flag to track if number is negative

	// Handle negative numbers - convert absolute value and add sign
	if (num < 0)
	{
		isNegative = 1;
		num = -num; // make it positive for conversion
	}

	// Special case: if number is 0
	if (num == 0)
	{
		printf("Binary: 0");
		return 0;
	}

	// Convert decimal to binary using repeated division by 2
	// Store remainders in array (they will be in reverse order)
	i = 0;
	while (num > 0)
	{
		arr[i] = num % 2; // remainder when divided by 2
		num = num / 2;	 // divide by 2 for next iteration
		i++;				 // move to next array position
	}

	// Display the binary number
	printf("Binary: ");
	if (isNegative)
		printf("-"); // add negative sign if original number was negative

	// Print digits in reverse order (most significant bit first)
	for (j = i - 1; j >= 0; j--)
	{
		printf("%d", arr[j]);
	}

	return 0;
}

// Converts decimal number to octal representation
// For negative numbers: converts absolute value and adds negative sign
int toOctal(int num)
{
	int isNegative = 0; // flag to track if number is negative
	int octalArr[32];   // array to store octal digits
	int k = 0;			// counter for octal array

	// Handle negative numbers
	if (num < 0)
	{
		isNegative = 1;
		num = -num; // make it positive for conversion
	}

	// Special case: if number is 0
	if (num == 0)
	{
		printf("Octal: 0");
		return 0;
	}

	// Convert decimal to octal using repeated division by 8
	while (num > 0)
	{
		octalArr[k] = num % 8; // remainder when divided by 8
		num = num / 8;		   // divide by 8 for next iteration
		k++;					   // move to next array position
	}

	// Display the octal number
	printf("Octal: ");
	if (isNegative)
		printf("-"); // add negative sign if original number was negative

	// Print digits in reverse order (most significant digit first)
	for (j = k - 1; j >= 0; j--)
	{
		printf("%d", octalArr[j]);
	}

	return 0;
}

// Converts decimal number to decimal (just displays it)
// This function is mainly for consistency in the conversion display
int toDecimal(int num)
{
	printf("Decimal: %d", num);
	return 0;
}

// Converts decimal number to hexadecimal representation
// For negative numbers: converts absolute value and adds negative sign
int toHexadecimal(int num)
{
	int isNegative = 0; // flag to track if number is negative
	int hexArr[32];	  // array to store hexadecimal digits
	int k = 0;			// counter for hex array
	char hexChars[] = "0123456789ABCDEF"; // characters for hex digits

	// Handle negative numbers
	if (num < 0)
	{
		isNegative = 1;
		num = -num; // make it positive for conversion
	}

	// Special case: if number is 0
	if (num == 0)
	{
		printf("Hexadecimal: 0");
		return 0;
	}

	// Convert decimal to hexadecimal using repeated division by 16
	while (num > 0)
	{
		hexArr[k] = num % 16; // remainder when divided by 16
		num = num / 16;		// divide by 16 for next iteration
		k++;					// move to next array position
	}

	// Display the hexadecimal number
	printf("Hexadecimal: ");
	if (isNegative)
		printf("-"); // add negative sign if original number was negative

	// Print digits in reverse order (most significant digit first)
	for (j = k - 1; j >= 0; j--)
	{
		printf("%c", hexChars[hexArr[j]]); // use hexChars array for A-F
	}

	return 0;
}

// Helper function to display all conversions for a given decimal number
void displayAllConversions(int decimalNum)
{
	printf("\n--- CONVERSION RESULTS ---\n");
	toBinary(decimalNum);
	printf("\n");
	toOctal(decimalNum);
	printf("\n");
	toDecimal(decimalNum);
	printf("\n");
	toHexadecimal(decimalNum);
	printf("\n");
	printf("------------------------\n\n");
}

// Function to exit the program gracefully
void exitProgram()
{
	printf("\nThank you for using NUMBER SYSTEM CONVERTER!\n");
	printf("Program terminated.\n\n");
	return;
}