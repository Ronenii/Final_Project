//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Concert header*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#include "main_header.h"
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
	ConcertInstrument ci_data;
	ConcertInstrument* next;
}CINode;

typedef struct
{
	ConcertInstrument* head;
	ConcertInstrument* tail;
}CIList;
typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

/*Function refrences*/

Concert getConcert();
void setConcertName(Concert* concert);
void setConcertDate(Concert* concert);
float getHourFromString(char* hour_string);
bool isDigit(char ch);
void checkMemoryAllocation(void* ptr);