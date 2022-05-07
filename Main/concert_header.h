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

Concert getConcert(InstrumentTree instrument_tree); 
void makeEmptyCIList(CIList* ci_list);

bool isDigit(char ch);
bool checkEmptyList(CIList* instrument_list);
bool checkIfMusicianExists(Musician** musicians_arr, int size_of_musician_arr, char* musician_name);

char* getString();

float getHourFromString(char* hour_string);

void insertCIDataToEndList(CIList* ci_list, CINode* new_ci_node);
void insertCINodeToEndList(CIList* ci_list, ConcertInstrument data);
void setConcertDate(Concert* concert);
void setConcertName(Concert* concert);
void printConcertHour(float time);
void printConcertDetails(Concert concert);
void setConcertInstruments(Concert* concert, InstrumentTree instrument_tree);
void setConcertInstrumentDetails(ConcertInstrument* concert_instrument, int instrument_id, CIList* ci_list);
