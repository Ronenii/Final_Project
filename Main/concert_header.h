//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Concert header*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#include "musician_header.h"
/*Constants*/
#define NAME_SIZE 150
#define HOUR_SIZE 6
#define FLOAT_CAST 100.0
#define HOUR_CALC 10
#define MEMORY_INCREASE 2


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
	CINode* head;
	CINode* tail;
}CIList;
typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;



/*Function refrences*/

Concert getConcert();
CIList createConcertInstrumentList();

bool isDigit(char ch);
bool checkEmptyList(CIList* instrument_list);
bool checkIfMusicianExists();

char* getString();

float getHourFromString(char* hour_string);

void insertDataToEndList(CIList* ci_list, CINode* new_ci_node);
void insertNodeToEndList(CIList* ci_list, ConcertInstrument data);
void makeEmptyConcertInstrumentList(CIList* ci_list);
void setConcertInstruments(Concert* concert);
void checkMemoryAllocation(void* ptr);
void setConcertDate(Concert* concert);
void setConcertName(Concert* concert);
void printConcertHour(float time);
void printConcertDetails(Concert concert);