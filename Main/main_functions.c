#include "main_header.h"


// The fucntion gets a string from the user and allocates memory due to the ammount of letters of the input untill \n is being inserted. 
// O(n) - n is the string input length. 
char* getString()
{
	int logSize = 0, phySize = 1;
	char c;
	char* string = (char*)malloc(sizeof(char) * phySize); // sets memory for first char. 
	checkMemoryAllocation(string);
	c = getchar();
	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= PHYSIC_SIZE_INCREASE; // for realloc allocation the pyhsical size need to be multiplied by two. 
			string = (char*)realloc(string, sizeof(char) * phySize);
			checkMemoryAllocation(string);
		}
		string[logSize] = c;
		logSize++;
		c = getchar();
	}
	string[logSize] = '\0'; // end of string. 
	return string;

}

void checkFileOpening(FILE* f)
{
	if (f == NULL)
	{
		printf("Error opening file, exiting.");
		exit(1);
	}
}

void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed, exiting.");
		exit(1);
	}
}

void printGoodbyeMessage()
{
	printf("Enjoy the shows :-)\n\n\n");
}