//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Concert header*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#include "main_header.h"
/*Constants*/
#define NAME_SIZE 150
#define HOUR_SIZE 6
#define FLOAT_CAST 100.0
#define HOUR_CALC 10


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
char* getString();
