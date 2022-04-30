#include "main_header.h"

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