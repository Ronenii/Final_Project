//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Musician functions*/
#include "musician_header.h"

/*Functions*/


//Returns an array of pointers to musicians, built from the musicians text file.
//o(n) = n^2(n is the number of musicians)
Musician** GetMusiciansFromFile(char * file_name, InstrumentTree tree)
{
	int physical_size=1, logical_size=0;
	char* textLine[LINE_LENGTH];

	FILE* file = fopen(file_name, "r");
	Musician** musician_ptr_arr = (Musician**)malloc(sizeof(Musician*)*physical_size);
	checkMemoryAllocation(musician_ptr_arr);
	fgets(textLine,LINE_LENGTH,file);
	while (feof(file) == 0)
	{
		musician_ptr_arr[logical_size] =getMusician(textLine,tree);
		logical_size++;
		if (logical_size == physical_size)
		{
			physical_size *= 2;
			musician_ptr_arr = (Musician**)realloc(musician_ptr_arr, sizeof(Musician*) * physical_size);
		}
		fgets(textLine, LINE_LENGTH, file);
	}
	fclose(file);
	return musician_ptr_arr;
}

//Recieves a text line and returns a musician pointer built from the values stored in it.
Musician* getMusician(char* line, InstrumentTree tree)
{
	Musician* musician = (Musician*)malloc(sizeof(musician));

	return musician;
}