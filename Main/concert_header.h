//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Concert header*/


#pragma once
/*Constants*/


/*Structs*/
typedef struct
{
	int day, month, year;
	float hour;
} Date;

typedef struct
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;

typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

/*Function refrences*/